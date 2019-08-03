#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

unsigned char FND_SEGNP[10] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x6F };
unsigned char FND_SEGPOS[4] = { 0x01, 0x02, 0x04, 0x08 };

unsigned int _pow[5] = { 1, 10, 100, 1000,10000 };

#define MOTOR_PORT      PORTD
#define MOTOR_PORT_DDR   DDRD

#define SENSOR_PORT      PINC


//running
#define STOP 0
#define RUN 1
#define BUFFER 2

//run state
#define STRAIGHT 2
#define LEFT_COR 3 //left correction
#define RIGHT_COR 4 //right correction
#define TURN_LEFT 5 //intersection turn left
#define TURN_RIGHT 6//intersection turn right
#define TEMP 7


//SENSOR
#define center 0x0F         //1111
#define right 0x0B         //1011
#define right_all 0x03      //0011
#define left 0x0D         //1101
#define left_all 0x0C      //1100
#define inter_left 0x0E      //1110
#define inter_right 0x07   //0111
#define stop_s   0x06      //0110

volatile unsigned int state = STRAIGHT;
volatile unsigned int reference_state = STRAIGHT;
volatile unsigned int last_state = 0;
volatile unsigned int cnt = 0;
volatile unsigned int turn_cnt = 0;
volatile unsigned int buffer_cnt = 0;
volatile unsigned int hurry_correction = 0;
volatile unsigned int stop_sign = 0;
volatile unsigned int stop_sign_edge = 0;
volatile unsigned int debug = 0;
volatile unsigned int left_flag = 0;
volatile unsigned int right_flag = 0;
volatile unsigned int hurry_left_correction = 0;
volatile unsigned int hurry_right_correction = 0;

volatile unsigned int straight_before_turn_left_cnt = 0;
volatile unsigned int straight_before_turn_right_cnt = 0;
volatile unsigned int T = 50; //In 44, max_vel
volatile unsigned int T2 = 47;
volatile unsigned char sensor = 0x0f;
//volatile unsigned char last_sensor = 0x0f;
//volatile unsigned char last_last_sensor = 0x0f;
volatile unsigned char stepleft = 0, stepright = 0;
volatile unsigned int running = STOP;
volatile unsigned int l_delay = 0, r_delay = 0;

volatile unsigned int left_sign_stack = 0;
volatile unsigned int right_sign_stack = 0;

volatile unsigned int back_left = 0;
volatile unsigned int back_right = 0;
volatile unsigned char BUFFER_endFlag = 0;
void port_init(void);
void init_devices(void);
unsigned char  LEFTmotorOneClock(unsigned char step, char dir);
unsigned char  RIGHTmotorOneClock(unsigned char step, char dir);

int main() {

   init_devices();
   MOTOR_PORT_DDR = 0xff;
   unsigned int j = 0;
   while (1) {


      PORTE = 0X04;
      if (running != BUFFER)
         PORTA = FND_SEGPOS[0];
      else
         PORTA = 0x0F;

      PORTE = 0X00;
      PORTE = 0X08;
      PORTA = FND_SEGNP[state % 10];
      PORTE = 0X00;
      _delay_ms(100);

      switch (running) {
      case RUN:
         //debug = 1;
         TCCR0 = _BV(CS00);
         break;
      case STOP:
         //debug = 2;
         TCCR0 = 0x00;
         TCNT0 = 0x00;
         break;
      case BUFFER:
         TCCR0 = _BV(CS00);
         break;
      }
   }
   return 1;
}


ISR(INT5_vect) {
   if (running == STOP) {
      running = RUN;
      TIMSK = 0x01; //timer interrupt sources

   }
   else
      running = STOP;
   EIFR = 0xFF;
}
ISR(TIMER0_OVF_vect)
{
   cnt++;
   if (cnt == T)
   {   
      cnt = 0;
      if (hurry_left_correction == 1 || hurry_right_correction == 1)
      {
         hurry_correction++;
         if (hurry_correction == 90)
         {
            hurry_left_correction = 0;
            hurry_right_correction = 0;
         }
      }
      if ((BUFFER_endFlag == 1) && (sensor == left_all))
         back_left++;
      else if ((BUFFER_endFlag == 1) && (sensor == right_all))
         back_right++;
      else if ((back_left == 800) || (back_right == 800))
         BUFFER_endFlag = 0;

      sensor = SENSOR_PORT & 0x0F;
      if (running == BUFFER)
      {   // 좌우양끝 센서를 1로 만들어 강제 흰색으로 인식시켜서 몸체쪽 두 센서로만 중심 잡도록시도>> BUFFER모드 추가이유
         sensor = (sensor | 0x09);   // sensorout1, sensorout4를 강제로 '1'로 set
         buffer_cnt++;
         if (buffer_cnt == 350) // Timer0_OVF_vect가 900번발생하면 다시 RUN모드로 전환
         {
            running = RUN;   buffer_cnt = 0;
            if ((SENSOR_PORT | 0xFE) != 0xFF)
            {
               //sensor = left_all;
               BUFFER_endFlag = 1;
               back_left = 0;
            }
            if ((SENSOR_PORT | 0xF7) != 0xFF)
            {
               //sensor = right_all;
               BUFFER_endFlag = 1;
               back_right = 0;
            }
            buffer_cnt = 0;
         }
      }
      if (left_flag == 1 || right_flag == 1 || hurry_left_correction == 1 || hurry_right_correction == 1) { last_state = state; } //when you want to remain the stage

      if ((BUFFER_endFlag == 1) && (back_left < 800))
         sensor = left_all;
      else if ((BUFFER_endFlag == 1) && (back_right < 800))
         sensor = right_all;

      switch (sensor) {
      case center:
         //if (stop_sign > 0) { stop_sign_edge++; stop_sign = 0; }
         state = STRAIGHT;
         //reference_state = state;
         break;
      case right:
         state = RIGHT_COR;
         //reference_state = state;
         break;
      case right_all:
         state = RIGHT_COR;
         //reference_state = state;
         break;
      case left:
         state = LEFT_COR;
         //reference_state = state;
         break;
      case left_all:
         state = LEFT_COR;
         //reference_state = state;
         break;
      case inter_left:
         left_sign_stack++;
         if (right_sign_stack > 0) { stop_sign++; right_sign_stack = 0; left_sign_stack = 0; break; }
         if (reference_state == STRAIGHT)
                  state = TURN_LEFT;   
         else
         {
            hurry_right_correction = 1;
            state = RIGHT_COR;
         }
         //state = STRAIGHT; //for debug
         //reference_state = state;
         break;
      case inter_right:
         right_sign_stack++;
         if (left_sign_stack > 0) { stop_sign++; right_sign_stack = 0; left_sign_stack = 0; break; }
         if (reference_state == STRAIGHT)
            state = TURN_RIGHT;
         else
         {
            hurry_left_correction = 1;
            state = LEFT_COR;
         }
         //state = TURN_RIGHT; //for debug
         //reference_state = state;
         break;
      case stop_s:
         //debug = 9;
         //stop_sign++;
         state = STRAIGHT;
         //reference_state = state;
         break;
      default:
         state = state;
         //reference_state = state;
         break;
      }
      if (left_flag == 1 || right_flag == 1 || hurry_left_correction == 1 || hurry_right_correction == 1) { state = last_state; }
      switch (state) {
      case STRAIGHT:
         stepright = RIGHTmotorOneClock(stepright, 1);
         stepleft = LEFTmotorOneClock(stepleft, 0);
         break;
      case LEFT_COR:   // Need to move left
         stepright = RIGHTmotorOneClock(stepright, 1);
         if (l_delay % 2 == 1)
         {
            stepleft = LEFTmotorOneClock(stepleft, 0);
         }
         l_delay++;
         break;
      case RIGHT_COR:   // Need to move right
         stepleft = LEFTmotorOneClock(stepleft, 0);
         if (r_delay % 2 == 1)
         {
            stepright = RIGHTmotorOneClock(stepright, 1);
         }
         r_delay++;
         break;
      case TURN_LEFT:
         left_flag = 1;
         TIMSK = 0x41;
         while (straight_before_turn_left_cnt<100)
         {
            straight_before_turn_left_cnt++;

            stepright = RIGHTmotorOneClock(stepright, 1);
            stepleft = LEFTmotorOneClock(stepleft, 0);
            break;
         }
         debug = 3;
         stepright = RIGHTmotorOneClock(stepright, 1);
         if (l_delay % 2 == 1)
         {
            stepleft = LEFTmotorOneClock(stepleft, 0);
         }
         l_delay++;
         break;
      case TURN_RIGHT:
         right_flag = 1;
         TIMSK = 0x41;
         while (straight_before_turn_right_cnt<85)
         {
            straight_before_turn_right_cnt++;

            stepright = RIGHTmotorOneClock(stepright, 1);
            stepleft = LEFTmotorOneClock(stepleft, 0);
            break;
         }
         debug = 4;
         stepleft = LEFTmotorOneClock(stepleft, 0);
         if (r_delay % 2 == 1)
         {
            stepright = RIGHTmotorOneClock(stepright, 1);
         }
         r_delay++;
         break;
      case
      default:
         stepright = RIGHTmotorOneClock(stepright, 1);
         stepleft = LEFTmotorOneClock(stepleft, 0);
         break;
      }

      MOTOR_PORT = stepleft | stepright;
   }
}
ISR(TIMER2_OVF_vect)
{
   turn_cnt++;
   if (turn_cnt == T2)   // T2값과 회전모드에 머무르는 시간이 비례
   {
      right_flag = 0;
      left_flag = 0;   // state 'TURN_LEFT'에 더이상 머무르지 않도록
      TIFR = 0x40;   // TIMER2_OVF_vect Flag강제로 내림
      TIMSK = 0x01;   // TIMER에 대한 인터럽트는 TIMER0 만 허용토록
      running = BUFFER;
   }
}
void port_init(void)
{
   PORTA = 0x00;
   DDRA = 0xFF;
   PORTB = 0x00;
   DDRB = 0x00;
   PORTC = 0x00;
   DDRC = 0x00;
   PORTD = 0x00;
   DDRD = 0xFF;
   PORTE = 0x04;
   DDRE = 0x0C;
   PORTF = 0x00;
   DDRF = 0x00;
   PORTG = 0x00;
   DDRG = 0x03;
}

void init_devices(void)
{
   cli(); //disable all interrupts
   XDIV = 0x00; //xtal divider
   XMCRA = 0x00; //external memory
   port_init();

   MCUCR = 0x00;
   EICRA = 0x00; //extended ext ints
   EICRB = 0x08; //extended ext ints
   EIMSK = 0x20;
   EIFR = 0xFF;
   TCCR0 = 0x00;
   TCCR2 = 0x05;
   TCNT0 = 0x00;
   TCNT2 = 0x00;
   //TIMSK = 0x01; //timer interrupt sources
   TIFR = 0xFF;
   ETIMSK = 0x00; //extended timer interrupt sources
   sei(); //re-enable interrupts
         //all peripherals are now initialized
}

/* Stepping Motor derive---------------------------*/
unsigned char  LEFTmotorOneClock(unsigned char step, char dir)
{
   step = step & 0x0f;
   if (dir) {
      switch (step) {
      case 0x09: step = 0x01; break;
      case 0x01: step = 0x03; break;
      case 0x03: step = 0x02; break;
      case 0x02: step = 0x06; break;
      case 0x06: step = 0x04; break;
      case 0x04: step = 0x0c; break;
      case 0x0c: step = 0x08; break;
      case 0x08: step = 0x09; break;
      default: step = 0x0c; break;
      }
   }
   else {
      switch (step) {
      case 0x09: step = 0x08; break;
      case 0x01: step = 0x09; break;
      case 0x03: step = 0x01; break;
      case 0x02: step = 0x03; break;
      case 0x06: step = 0x02; break;
      case 0x04: step = 0x06; break;
      case 0x0c: step = 0x04; break;
      case 0x08: step = 0x0c; break;
      default: step = 0x0c; break;
      }
   }
   return step;

}


/* Stepping Motor derive---------------------------*/
unsigned char  RIGHTmotorOneClock(unsigned char step, char dir)
{
   step = step & 0xf0;
   if (dir) {
      switch (step) {
      case 0x90: step = 0x10; break;
      case 0x10: step = 0x30; break;
      case 0x30: step = 0x20; break;
      case 0x20: step = 0x60; break;
      case 0x60: step = 0x40; break;
      case 0x40: step = 0xc0; break;
      case 0xc0: step = 0x80; break;
      case 0x80: step = 0x90; break;
      default: step = 0xc0; break;
      }
   }
   else {
      switch (step) {
      case 0x90: step = 0x80; break;
      case 0x10: step = 0x90; break;
      case 0x30: step = 0x10; break;
      case 0x20: step = 0x30; break;
      case 0x60: step = 0x20; break;
      case 0x40: step = 0x60; break;
      case 0xc0: step = 0x40; break;
      case 0x80: step = 0xc0; break;
      default: step = 0xc0; break;
      }
   }
   return step;
}


void delay(int n)
{
   volatile int i, j;
   for (i = 1; i<n; i++)
   {
      for (j = 1; j<400; j++);
   }
}



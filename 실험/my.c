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

#define ENDCOUNT 3
#define ENDCONDITION(i) (i >= ENDCOUNT)
#define SENSING(i) (i = PINC)
int ENDCNT = 999;

#define DefaultFreq 50

#define OneMoveFreq 40

//out
#define Nothing       0x00
#define LeftLineDect  0x02
#define RightLineDect 0x04
#define Cross         0x06

//in sensor
#define LeftWing    0x01
#define RightWing   0x08
#define Both 0x09

//act body
#define Straight 0
#define LLM 1
#define RLM 2

// act wing
#define TurnLeft 3
#define TurnRight 4
#define X 5
#define IncreaseEndCNT 6
#define START 1
#define TempA 7

//SENSOR
#define center 0x0F         //1111
#define right 0x0B         //1011
#define right_all 0x03      //0011
#define left 0x0D         //1101
#define left_all 0x0C      //1100
#define inter_left 0x0E      //1110
#define inter_right 0x07   //0111
#define stop_s   0x06      //0110

#define DleftOffset 30
#define DrightOffset 50

volatile int state = 0;
volatile int prestate = 0;
volatile int nextstate = 0;
volatile int mainstate = 0;

volatile unsigned int temp = 0;
volatile unsigned int cnt = 0;



volatile unsigned char LeftStep  = 0;
volatile unsigned char RightStep  = 0;

volatile unsigned char freqLeft = 0;
volatile unsigned char freqRight = 0;

volatile unsigned int LLMOffset = 0;
volatile unsigned int RLMOffset = 0;
#define DefaultOffset 40


volatile unsigned char  LEFTmotorOneClock(volatile unsigned char step, char dir);
volatile unsigned char  RIGHTmotorOneClock(volatile unsigned char step, char dir);

void straight(){
   if(prestate == Straight)
      freqLeft = freqRight;// -= 10;
   else
      freqLeft = freqRight = DefaultFreq;
}

void llm(){
   if(prestate == LLM)
      LLMOffset = LLMOffset;// + 10;
   else LLMOffset = DefaultOffset;

   freqRight += LLMOffset;

}

void rlm(){
   if(prestate == RLM)
      RLMOffset = RLMOffset;// + 10;
   else RLMOffset = DefaultOffset;

   freqLeft += RLMOffset;
}

void putMotorValue(){
   if(cnt % freqLeft == 0)
      LeftStep = LEFTmotorOneClock(LeftStep, 0);

   if(cnt % freqRight == 0)
      RightStep = RIGHTmotorOneClock(RightStep, 1);
}

void setNextState(){
   volatile int inSensor = PINC & 0x06;
   volatile int outSensor = PINC & 0x09;

   switch(inSensor){
      case Nothing:
         nextstate = Straight;
         break;
      case LeftLineDect:
         nextstate = LLM;
         break;
      case RightLineDect:
         nextstate = RLM;
         break;
      case Cross:
         nextstate = Straight;
         break;
   }

   switch(outSensor){
      case LeftWing:
         if(prestate == TempA)
            mainstate = TurnLeft;
         else mainstate = TempA;
         break;
      case RightWing:
         if(prestate == TempA)
            mainstate = TurnRight;
         else mainstate = TempA;
         break;
      case Both:
         if(inSensor == Cross)
            mainstate = X;
         else mainstate = IncreaseEndCNT;
         break;
   }

   if(cnt % 3 == 0)
      prestate = state;
};

ISR(TIMER0_OVF_vect)
{		
	TCNT0 = 0;
   temp++;
   if(temp == OneMoveFreq){
     state = nextstate;
	  temp = 0;
      cnt++;
      switch(state){

         case Straight:
            straight();
            break;

         case LLM:
            llm();
            break;
			
         case RLM:
            rlm();
            break;
      }
      setNextState();
      putMotorValue();
   }
}

int LedMEETSLine(){
   if((SENSOR_PORT & 0x06) == 0x06)
      freqLeft = freqRight += 1;
   else if((SENSOR_PORT & 0x06) == 0x02)
      OCR0 -=1;
   else if((SENSOR_PORT & 0x06) == 0x04)
      OCR2 -=1;

   return (SENSOR_PORT & 0x0F) != 0x0F;
} 

int LedNoneDectected(int i){
   switch(i){
      case TurnLeft :
         OCR2 -= 1;
         OCR0 = 255;
         break;
      case TurnRight :
      break;
   }
   
   return (SENSOR_PORT & 0x0F) == 0x0F;
}

void initPort(void);
void init_devices(void);

int main() {
   initPort();
   init_devices();
   MOTOR_PORT_DDR = 0xff;
   while (1) {
      PORTE = 0X04;
      PORTA = FND_SEGPOS[0];

      PORTE = 0X00;
      PORTE = 0X08;
      PORTA = FND_SEGNP[state % 10];
      PORTE = 0X00;
      if(ENDCNT < 3){
         switch(state){
            case START :
            break;
         
            case Straight:
            break;

            case TurnLeft:
            break;
            
            case TurnRight:
            break;

            }
		}
    }
   return 1;
}

ISR(INT5_vect) {
  ENDCNT = 0; //timer interrupt sources
  TIMSK = 0x01;
  nextstate = Straight;
}

// ISR(TIMER2_OVF_vect)
// {
//    turn_cnt++;
//    if (turn_cnt == T2)   // T2값과 회전모드에 머무르는 시간이 비례
//    {
//       right_flag = 0;
//       left_flag = 0;   // state 'TURN_LEFT'에 더이상 머무르지 않도록
//       TIFR = 0x40;   // TIMER2_OVF_vect Flag강제로 내림
//       TIMSK = 0x01;   // TIMER에 대한 인터럽트는 TIMER0 만 허용토록
//       running = BUFFER;
//    }
// }
void initPort(void)
{
DDRC = 0x00;
DDRA = 0xFF;
DDRE |= (_BV(2)|_BV(3));
PORTE |= (_BV(2));
PORTA = 0x0F;
PORTE |= (_BV(3));
PORTA = 0x00;
DDRD  = 0xFF;
DDRF  = 0xF0;
}

void init_devices(void)
{
   cli(); //disable all interrupts

XMCRA = 0x00; //external memory

EICRA = 0x00; //extended ext ints
EICRB = 0x08; //extended ext ints
EIMSK = 0x20;
EIFR = 0x00;

	TCCR0 = 0x03;
	TCNT0 = 0;
	TIMSK = 0x01;
   //TIMSK = 0x01; //timer interrupt sources
   TIFR = 0xFF;
   sei(); //all peripherals are now initialized
}

/* Stepping Motor derive---------------------------*/
volatile unsigned char  LEFTmotorOneClock(volatile unsigned char step, char dir)
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
volatile unsigned char  RIGHTmotorOneClock(volatile unsigned char step, char dir)
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

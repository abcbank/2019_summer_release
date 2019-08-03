#include <avr/io.h>

#include <util/delay.h>

unsigned char FND_SEGNP[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x6F};

unsigned char FND_SEGWP[10] = {0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0xA7,0xFF,0xEF};

unsigned char FND_SEGPOS[4]   = {0x01, 0x02, 0x04, 0x08};

int _pow[5] = {1, 10, 100, 1000,10000};

unsigned char LED_ON[4] = { 0X10,0X20,0X40,0X80 };

void init_port(){
   DDRA = 0xFF;
   DDRE = 0x0C;
   PORTE = 0x04;
   PORTA = 0x0F;
   DDRG = 0x00;
   DDRF = 0xF0;
   PORTF = 0x00;
}

int main(){
   init_port();
   int i = 0, cnt;

   while (1) {
      cnt = 0;
      while (1) {
         for (i = 0; i < 4; i++)
         {
            PORTA = FND_SEGPOS[i];
            PORTE = 0X04;
            PORTE = 0X00;
            if (i == 1)
               PORTA = FND_SEGNP[(cnt / _pow[2]) % _pow[1]];
            else if (i == 2) {
               PORTA = FND_SEGNP[(cnt%_pow[2]) / _pow[1]];
            }
            else if (i == 3) {
               PORTA = FND_SEGNP[cnt%_pow[1]];
            }
            else
            {
               PORTA = FND_SEGNP[cnt / _pow[3]];
            }
            PORTE = 0X08;
            PORTE = 0X00;
            _delay_us(2500);
         }
         if (!(PING & 0X08)) {
            while (!(PING & 0X08));
            cnt++;
         }
         else if (!(PING & 0X04)) {
            while (!(PING & 0X04));
            cnt--;
            if(cnt<0)
               cnt = 10000;
         }
      }
   }
}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define next_line "\n\r"
#define space "     "

void change(long x, char pos[])
{
   pos[3] = x % 10 + 48;
   x /= 10;
   pos[2] = x % 10 + 48;
   x /= 10;
   pos[1] = x % 10 + 48;
   x /= 10;
   pos[0] = x % 10 + 48;
}

int main()
{
   int j;
   int cx, cy;
   char c, d;
   char pos[4];
   char X[] = "X = ";
   char Y[] = "Y = ";
   char save[5];

   HANDLE hSerial;
   POINT a;

   unsigned long bytes_written;
   DCB dcbSerialParams = { 0 };
   COMMTIMEOUTS timeouts = { 0 };

   HANDLE hIn, hOut;
   INPUT_RECORD rec;
   DWORD dw;

//   DWORD dwBytesRead;

   hIn = GetStdHandle(STD_INPUT_HANDLE);
   hOut = GetStdHandle(STD_OUTPUT_HANDLE);

   hSerial = CreateFile("COM2", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if (hSerial == INVALID_HANDLE_VALUE)
   {
      if (GetLastError() == ERROR_FILE_NOT_FOUND)
         printf("ERROR!! COM2 PORT NOT FOUND\n");
      printf("ERROR!! FAIIED TO ACCESS TO COM2 SUCCESSFULLY\n");
   }

   dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

   if (!GetCommState(hSerial, &dcbSerialParams))
      printf("ERROR!! FAIIED TO GET SERIAL PARAMETERS\n");

   dcbSerialParams.BaudRate = CBR_57600;
   dcbSerialParams.ByteSize = 8;
   dcbSerialParams.Parity = NOPARITY;
   dcbSerialParams.StopBits = ONESTOPBIT;

   if (!SetCommState(hSerial, &dcbSerialParams))
      printf("ERROR, Setting serial port state");

   timeouts.ReadIntervalTimeout = 50;
   timeouts.ReadTotalTimeoutConstant = 50;
   timeouts.ReadTotalTimeoutMultiplier = 10;
   timeouts.WriteTotalTimeoutConstant = 50;
   timeouts.WriteTotalTimeoutMultiplier = 10;

   if (!SetCommTimeouts(hSerial, &timeouts))
   {
      printf("ERROR!! Time Out\n");
      return;
   }
   else
   {
      while (1)
      {
         ReadConsoleInput(hIn, &rec, 1, &dw);
         if(rec.Event.MouseEvent.dwEventFlags){
         GetCursorPos(&a); //커서의 좌표를 알아오는 함수, a는 전체 화면 기준으로 커서의 좌표를 받아올 POINT 구조체의 포인터로써 &a를 써준다.
//         printf("X = %d , Y = %d\n", a.x, a.y);

         change(a.x,pos);  //입력받은 x좌표의 int값을 문자열로 변환한다. 왜냐하면 putty에선 문자열만 출력할 수 있기 때문이다. 
         WriteFile(hSerial, X, sizeof(X), &bytes_written, NULL); //char형의 X을 putty에 출력한다. 위에 보면 "x = "으로 선언되어 있는것을 볼수 있다.
         WriteFile(hSerial, pos, 4*sizeof(char), &bytes_written, NULL); //char형으로 변환된 값을 출력한다.
         WriteFile(hSerial, space, sizeof(space), &bytes_written, NULL); // " "를 putty에 출력한다. 

                                       //WriteFile함수는 파일데이터를 쓰는 함수이다. 위에 보면 hserial 을 통해 파일을 생성했다. 
                                       //(파일, 파일이나 장치에 기록할 데이터를 가지고 있는 버퍼의 포인터, 기록할데이터의 길이, 기록한 데이터의 바이트 수를 리턴받는 인수, 비동기입출력을 위한 OVERLAPPED 구조체의 포인터 비동기 입출력을 사용하지 않을 경우에는 NULL 값으로 지정해야 한다. )


         change(a.y, pos);  //입력받은 y좌표의 int값을 문자열로 변환한다. 왜냐하면 putty에선 문자열만 출력할 수 있기 때문이다.
         WriteFile(hSerial, Y, sizeof(Y), &bytes_written, NULL); //char 형의 Y를 putty에 출력한다 . 위에 보면 "y = "으로 선언되어 있는것을 볼 수 있다.
         WriteFile(hSerial, pos, 4*sizeof(char), &bytes_written, NULL); //char형으로 변환된 q값을 putty에 출력한다 
         WriteFile(hSerial, next_line, sizeof(next_line), &bytes_written, NULL); //" \n"를 putty에 출력한다 

         ReadConsoleInput(hIn, &rec, 1, &dw); //여기서부터 "dw"를 사용한다. 이 변수는 마우스의 이벤트를 저장, 그것은 마우스를 사용하게 됨을 의미
                              //콘솔 입력된 버퍼에서 데이터를 읽어들이고 버퍼에서 제거합니다.

         if (rec.Event.MouseEvent.dwEventFlags& DOUBLE_CLICK) //마우스 이벤트가 더블클릭일 경우
         {
            printf("Doubleclick!!\n"); //더블클릭을 했다. 출력
            WriteFile(hSerial, "Doubleclick", 12, &bytes_written, NULL); //"Doubleclik"을 putty에 출력한다. 
            WriteFile(hSerial, next_line, sizeof(next_line), &bytes_written, NULL); //" \n"을 putty에 출력.
            WriteFile(hSerial, X, sizeof(X), &bytes_written, NULL); //"x : "를 출력

            j = 0;

            while (1)
            {
               ReadFile(hSerial, &c, sizeof(char), &bytes_written, NULL);
               // ReadFile함수는 데이터를 읽는 함수이다. 
               //(파일이나 장치의 핸들, 데이터를 받아올 버퍼의 포인터, 읽어올 데이터의 길이, 읽어들인 데이터 바이트의 수를 리턴받는 인수, 비동기 입출력을 사용하지 않을 경우에는 NULL 값으로 지정해야 합니다.)

               if (bytes_written == 1) { // 파일이 쓰여져 있다면
                  if (c == '\r') //만약 putty에서 엔터가 눌리면
                  {
                     save[j] = '\0';
                     break; //break한다. 
                  }
                  save[j] = c;  //j에 c 문자열을 저장한다. 그리고 j는 +1이 된다.
                  WriteFile(hSerial, &save[j++], sizeof(char), &bytes_written, NULL); //char형으로 변환된 q값을 putty에 출력한다.
               }
            }

            WriteFile(hSerial, next_line, sizeof(next_line), &bytes_written, NULL); // " "를 putty에 출력한다. 


//            printf("입력받은 좌표 값은 ");
            printf("Xpos = %s\n", save); //ax를 출력한다.
            cx = atoi(save);
            WriteFile(hSerial, Y, sizeof(Y), &bytes_written, NULL); // "y : "를 출력

            j = 0;

            while (1)
            {
               ReadFile(hSerial, &d, sizeof(char), &bytes_written, NULL);

               if (bytes_written == 1) { //읽어온 데이터가 있으면 1이고 없으면 0이기 때문에 만약, 1이면
                  if (d == '\r')
                  {
                     save[j] = '\0';
                     break;
                  }
                  save[j] = d; //save[j++]에 d를 저장
                  WriteFile(hSerial, &save[j++], sizeof(char), &bytes_written, NULL); //char형으로 변환된 q값을 putty에 출력한다
               }
            }
            cy = atoi(save);
            WriteFile(hSerial, next_line, sizeof(next_line), &bytes_written, NULL); //" \n"를 putty에 출력한다 
            printf("Ypos = %s\n", save);
            SetCursorPos(cx, cy);
            c = '0';
            d = '0';
         }
      }
      }
   }
   CloseHandle(hSerial);
   system("pause");
   return 0;
}
#include <Arduino.h>


const int latchPin = 12; //пин соединяем с ST_CP сдв.регистра 74HC595
const int clockPin = 8; //пин соединяем с SH_CP сдв.регистра 74HC595
const int dataPin = 11; //пин соединяем с DS сдв.регистра 74HC595
//Столбцы
int data[] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//Null
              0x00,0x3E,0x48,0x88,0x88,0x48,0x3E,0x00, //A
              0x00,0x00,0x0C,0x12,0x12,0xFE,0x00,0x00, //d
              0x00,0x00,0x7C,0x92,0x92,0x92,0x70,0x00, //e
              0x00,0x00,0x7C,0x92,0x92,0x92,0x70,0x00, //e
              0x00,0x00,0xFE,0x90,0x90,0x60,0x00,0x00, //p
              0x00,0x00,0x10,0x10,0x7E,0x12,0x10,0x00, //t
              0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00  //Null
              };              
//Строки       
unsigned char  tab[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};  
 
void setup () {
  //пины на вывод
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
}
void loop() {
    for(int n = 0; n < 56; n++)
    {
        for(int t=0;t<100;t++)
        {
            for(int num=n; num < 8+n; num++)
            {                       
                shiftOut(dataPin,clockPin,MSBFIRST,data[num]); //посылаем данные (столбцы) функцией shiftOut ( http://arduino.ru/Reference/ShiftOut )
                shiftOut(dataPin,clockPin,MSBFIRST,tab[num-n]); //посылаем данные (строки) функцией shiftOut
                digitalWrite(latchPin,HIGH);
                digitalWrite(latchPin,LOW);
            }
        }
    }
}
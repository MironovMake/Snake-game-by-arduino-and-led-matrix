#include "LedControl.h"
#include "binary.h"

/*
 Контакт DIN на матрице – к цифровому контакту 12 на Arduino
 Контакт CLK – к цифровому контакту 11
 Контакт CS – к цифровому контакту 10
*/
LedControl lc = LedControl(12, 11, 10, 1);

// задержка между разными рожицами:
unsigned long delaytime = 500;

// веселая рожица:
byte hf[8] = {B00111100, B01000010, B10100101, B10000001, B10100101, B10011001, B01000010, B00111100};
// «покерфейс»:
byte nf[8] = {B00111100, B01000010, B10100101, B10000001, B10111101, B10000001, B01000010, B00111100};
// грустная рожица:
byte sf[8] = {B00111100, B01000010, B10100101, B10000001, B10011001, B10100101, B01000010, B00111100};

void setup()
{
  Serial.begin(9600);
  lc.shutdown(0, false);
  // выставляем яркость на среднее значение:
  lc.setIntensity(0, 8);
  // очищаем дисплей:
  lc.clearDisplay(0);
  Serial.println();
}

void drawFaces()
{
  int i = 0;
  while (i < 8)
  {
    lc.setRow(0, i, nf[i]);
    Serial.println(i);
    i++;
  }
  delay(2000);
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, hf[i]);
  }
  delay(2000);
}

void loop()
{

  for (int i = 8; i > 0; i--)
  {
    lc.setLed(0, i, 1, 1);
    Serial.println(i);
    delay(500);
  }
  for (int i = 8; i > 0; i--)
  {
    lc.setLed(0, 1, i, 1);
    Serial.println(i);
    delay(500);
  }
  delay(2000);
}
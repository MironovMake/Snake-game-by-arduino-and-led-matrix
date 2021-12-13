#include "LedControl.h"
#include "binary.h"
LedControl lc = LedControl(12, 11, 10, 1);

// длинна зменйки
int lenght = 1;
// скорость змейки
int speed = 1000;
// карта
int mapp2[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}};
// положение фрукта
int fruit[] = {1, 2};
// текущая позиция на карте
int currentPosition[] = {3, 3};
// направления движения
int directionX = 1;
int directionY = 0;
// кнопки для управления
int buttonRight;
int buttonLeft;
int buttonUp;
int buttonDown;

void setup()
{
  pinMode(buttonRight, INPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);

  Serial.begin(9600);
  lc.shutdown(0, false);
  // выставляем яркость на среднее значение:
  lc.setIntensity(0, 8);
  // очищаем дисплей:
  lc.clearDisplay(0);
  Serial.println();
}

void moveLeft()
{
  for (int i = 8; i > 0; i--)
  {
    lc.setLed(0, i, 7, 1);
    Serial.println(i);
    delay(speed);
  }
}
void moveRight()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setLed(0, 0, i, 1);
    Serial.println(i);
    delay(speed);
  }
}
void moveUp()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setLed(0, i, 1, 1);
    Serial.println(i);
    delay(speed);
  }
}

void moveDown()
{
  for (int i = 8; i > 0; i--)
  {
    lc.setLed(0, 7, i, 1);
    Serial.println(i);
    delay(speed);
  }
}
void loop()
{
  moveLeft();
}
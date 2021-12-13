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
int directionX = 0;
int directionY = 0;
// кнопки для управления
int buttonRight = 3;
int buttonLeft = 2;
int buttonUp = 1;
int buttonDown = 13;

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
  int i = 8;
  while (directionX == -1)
  {
    lc.setLed(0, i, 7, 1);
    Serial.println(i);
    delay(speed);
    i--;
  }
}
void moveRight()
{
  int i = 0;
  while (directionX == 1)
  {
    lc.setLed(0, 0, i, 1);
    Serial.println(i);
    delay(speed);
    i++;
  }
}
void moveUp()
{
  int i = 0;
  while (directionY == 1)
  {
    lc.setLed(0, i, 1, 1);
    Serial.println(i);
    delay(speed);
    i++;
  }
}

void moveDown()
{
  int i = 8;
  while (directionY == -1)
  {
    lc.setLed(0, 7, i, 1);
    Serial.println(i);
    delay(speed);
    i--;
  }
}
void loop()
{
  if (digitalRead(buttonUp))
  {
    directionY = 1; // двигаемся вверх
    directionX = 0;
  }
  else if (digitalRead(buttonDown))
  {
    directionY = -1; // двигаемся вниз
    directionX = 0;
  }
  else if (digitalRead(buttonRight))
  {
    directionY = 0; // двигаемся вправо
    directionX = 1;
  }
  else if (digitalRead(buttonLeft))
  {
    directionY = 0; // двигаемся влево
    directionX = -1;
  }

  moveUp();
  moveDown();
  moveRight();
  moveLeft();
}
#include "LedControl.h"
#include "binary.h"
LedControl lc = LedControl(12, 11, 10, 1);
// длинна зменйки
int lenght = 1;
// скорость змейки
int speed = 1000;
unsigned long timer;
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
int currentPosX = 3;
int currentPosY = 3;
// предыдущая позиция на карте
int previousPosX;
int previousPosY;

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
  if (directionX == -1)
  {
    // текущее положение Х становится предыдущим
    previousPosX = currentPosX;
    // обговляем текущее положение Х (делаем шаг)
    currentPosX--;
    lc.setLed(0, currentPosY, currentPosX, 1);
    // сделали шаг
    // выключаем предыдущий светодиод
    lc.setLed(0, previousPosX, currentPosY, 0);
  }
}

void moveRight()
{
  if (directionX == 1)
  {
    // текущее положение Х становится предыдущим
    previousPosX = currentPosX;
    // обговляем текущее положение Х (делаем шаг)
    currentPosX++;
    lc.setLed(0, currentPosY, currentPosX, 1);
    // сделали шаг
    // выключаем предыдущий светодиод
    lc.setLed(0, previousPosX, currentPosY, 0);
  }
}
void moveUp()
{

  if (directionY == 1)
  {
    // текущее положение Х становится предыдущим
    previousPosY = currentPosY;
    // обговляем текущее положение Х (делаем шаг)
    currentPosY++;
    lc.setLed(0, currentPosY, currentPosX, 1);
    // сделали шаг
    // выключаем предыдущий светодиод
    lc.setLed(0, currentPosX, previousPosY, 0);
  }
}
void moveDown()
{

  if (directionY == -1)
  {
    // текущее положение Х становится предыдущим
    previousPosY = currentPosY;
    // обговляем текущее положение Х (делаем шаг)
    currentPosY--;
    lc.setLed(0, currentPosY, currentPosX, 1);
    // сделали шаг
    // выключаем предыдущий светодиод
    lc.setLed(0, currentPosX, previousPosY, 0);
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
  Serial.print("digitalRead(buttonUp)  ");
  Serial.println(digitalRead(buttonUp));
  Serial.print("digitalRead(buttonDown)  ");
  Serial.println(digitalRead(buttonDown));
  Serial.print("digitalRead(buttonRight)  ");
  Serial.println(digitalRead(buttonRight));
  Serial.print("digitalRead(buttonLeft)  ");
  Serial.println(digitalRead(buttonLeft));
  // раз в заданное время делаем шаг
  if (millis() - timer > speed)
  {
    timer = millis();
    moveLeft();
    moveUp();
    moveDown();
    moveRight();
  }
}
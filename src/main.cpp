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
bool fruitFlag = 1;
// текущая позиция на карте
int fruitX;
int fruitY;

int currentPosX = 3;
int currentPosY = 3;
// предыдущая позиция на карте
int previousPosX = currentPosX;
int previousPosY = currentPosY;

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
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);

  Serial.begin(9600);
  lc.shutdown(0, false);
  // выставляем яркость на среднее значение:
  lc.setIntensity(0, 8);
  // очищаем дисплей:
  lc.clearDisplay(0);
  Serial.println();
}

void moveX()
{
  if (!directionX)
  {
    // текущее положение Х становится предыдущим
    previousPosX = currentPosX;
    // обговляем текущее положение Х (делаем шаг)
    currentPosX = currentPosX + directionX;
    lc.setLed(0, currentPosY, currentPosX, 1);
    // сделали шаг
    if (fruitX == currentPosX && fruitY == currentPosY)
      fruitFlag = 1;
    // выключаем предыдущий светодиод
    lc.setLed(0, currentPosY, previousPosX, 0);
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
    lc.setLed(0, previousPosY, currentPosX, 0);
  }
}

void loop()
{
  if (fruitFlag)
  {
    fruitX = random(7);
    fruitY = random(7);
    while (fruitX == currentPosX && fruitX == currentPosX)
      fruitX = random(7);
    lc.setLed(0, fruitX, fruitY, 1);
    fruitFlag = 0;
  }

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
  Serial.print("directionX  ");
  Serial.println(directionX);
  Serial.print("directionY  ");
  Serial.println(directionY);

  // раз в заданное время делаем шаг
  if (millis() - timer > speed)
  {
    timer = millis();
    moveUp();
    moveDown();
    moveX();
    if (currentPosY > 7 || currentPosX > 7)
    {
      // проиграли начинаем заново
      directionX = 0;
      directionY = 0;
      lc.clearDisplay(0);
      currentPosX = 3;
      currentPosY = 3;
      previousPosX = currentPosX;
      previousPosY = currentPosY;
    }
  }
}
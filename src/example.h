#include "LedControl.h"
#include "binary.h"

// LedControl::LedControl(int dataPin, int clkPin, int csPin, int numDevices)
LedControl lc = LedControl(12, 11, 10, 1);
// скорость змейки
int speed = 1000;
unsigned long timer;

// положение фрукта
bool fruitFlag = 1;
int fruitX;
int fruitY;
int fruitCounter;
int XPositionBody[20];
int YPositionBody[20];
// длинна зменйки
int lenght = 1;
// текущая позиция на карте
int currentPosX = 3;
int currentPosY = 3;
// предыдущая позиция на карте
int previousPosX = currentPosX;
int previousPosY = currentPosY;

// направления движения
int directionX = 0;
int directionY = 0;
// кнопки для управления
int buttonRight = 2;
int buttonLeft = 5;
int buttonUp = 3;
int buttonDown = 4;

void step()
{
  // текущее положение Х становится предыдущим
  previousPosX = currentPosX;
  previousPosY = currentPosY;
  // обговляем текущее положение Х,Y (делаем шаг)
  currentPosX = currentPosX + directionX;
  currentPosY = currentPosY + directionY;
  lc.setLed(0, currentPosY, currentPosX, 1);
  // сделали шаг
  if (fruitX == currentPosX && fruitY == currentPosY)
  {
    fruitFlag = 1;
    lenght++;
    fruitCounter++;
  }
  if (fruitCounter = 5)
    speed = 500;
  // выключаем предыдущий светодиод
  if (!fruitFlag)
    lc.setLed(0, currentPosY, previousPosX, 0);
}

void setup()
{
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT);
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

void loop()
{
  if (digitalRead(buttonRight))
    Serial.println("buttonRight");
  if (digitalRead(buttonLeft))
    Serial.println("buttonLeft");
  if (digitalRead(buttonUp))
    Serial.println("buttonUp");
  if (digitalRead(buttonDown))
    Serial.println("buttonDown");

  // создаем фрукт на карте

  /*
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
    Serial.print("digitalRead(buttonUp)  ");
    Serial.println(digitalRead(buttonUp));
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
    step();
    // условие проигрыша
    if (currentPosY > 7 || currentPosX > 7 || currentPosY < 0 || currentPosX < 0)
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
  */
}

// работа с циклами
// генерировать случайные числа
// работа с дисплеем
//
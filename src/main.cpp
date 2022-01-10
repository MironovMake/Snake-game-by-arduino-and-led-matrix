#include "LedControl.h"
#include "binary.h"

// LedControl::LedControl(int dataPin, int clkPin, int csPin, int numDevices)
LedControl lc = LedControl(12, 11, 10, 1);
// скорость змейки
int speed = 300;
unsigned long timer;
bool startFlag = 1;
// положение фрукта
bool fruitFlag = 1;
int fruitX;
int fruitY;
int fruitCounter;
int bodyX[20];
int bodyY[20];

// длинна зменйки
int lenght = 2;
// текущая позиция на карте
int currentPosX = 3;
int currentPosY = 3;
// предыдущая позиция на карте
int previousPosX = currentPosX;
int previousPosY = currentPosY;
int counter;

// направления движения
int directionX = 0;
int directionY = 0;
// кнопки для управления
int buttonRight = 5;
int buttonLeft = 2;
int buttonUp = 3;
int buttonDown = 4;

void step()
{
  // старт
  if (startFlag)
  {
    lc.setLed(0, 3, 3, 0);
    startFlag = 0;
  } // текущее положение Х становится предыдущим

  // обговляем текущее положение Х,Y (делаем шаг)
  currentPosX = currentPosX + directionX;
  currentPosY = currentPosY + directionY;
  // координата головы
  bodyY[0] = currentPosY;
  bodyX[0] = currentPosX;

  lc.setLed(0, currentPosY, currentPosX, 1);
  // сделали шаг
  // lc.setLed(0, previousPosY, previousPosX, 0);
  if (fruitX == currentPosX && fruitY == currentPosY)
  {
    fruitFlag = 1;
    lenght++;
  }
  // до цикла bodyX[]={2,3,4,0}
  for (int i = lenght; i > 0; i--)
  {
    bodyX[i] = bodyX[i - 1];
    bodyY[i] = bodyY[i - 1];
  }
  // после цикла bodyX[]={1,2,3,4}
  lc.setLed(0, bodyY[lenght], bodyX[lenght], 0);
  //(lenght == 1) ? lc.setLed(0, previousPosY, previousPosX, 0) : lc.setLed(0, bodyY[lenght], bodyX[lenght], 0);
  previousPosX = currentPosX;
  previousPosY = currentPosY;
  lc.setLed(0, fruitY, fruitX, 1);
}

void frutGeneration()
{
  // сщетчик
  counter = 0;

  while ((counter + 2) < lenght)
  {
    counter = 0;
    fruitX = random(8);
    fruitY = random(8);
    // перебираем тело змеиSerial.println("counter  ");
    Serial.println(lenght);
    for (int i = lenght; i > 0; i--)
    {
      if (fruitX == bodyX[i] && fruitY == bodyY[i])
      {
        counter=0;
      }
      else
      {
        counter ++;
      }
    }
    Serial.print("counter  ");
    Serial.println(counter);
    Serial.print("lenght  ");
    Serial.println(lenght);
  }

  fruitFlag = 0;
  lc.setLed(0, fruitY, fruitX, 1);
  Serial.println("frut was generated");
}

void setup()
{
  Serial.println("GAME START");
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
  lc.setLed(0, currentPosY, currentPosX, 1);
}

void loop()
{

  if (digitalRead(buttonUp) && startFlag || digitalRead(buttonUp) && (directionX != 0 && startFlag == 0))
  {
    directionY = 1; // двигаемся вверх
    directionX = 0;
  }
  else if (digitalRead(buttonDown) && startFlag || digitalRead(buttonDown) && (directionX != 0 && startFlag == 0))
  {
    directionY = -1; // двигаемся вниз
    directionX = 0;
  }
  else if (digitalRead(buttonRight) && startFlag || digitalRead(buttonRight) && (directionY != 0 && startFlag == 0))
  {
    directionY = 0; // двигаемся вправо
    directionX = 1;
  }
  else if (digitalRead(buttonLeft) && startFlag || digitalRead(buttonLeft) && (directionY != 0 && startFlag == 0))
  {
    directionY = 0; // двигаемся влево
    directionX = -1;
  }

  // раз в заданное время делаем шаг
  if (millis() - timer > speed && (directionY != 0 || directionX != 0))
  {
    timer = millis();
    step();

    // условие проигрыша
    if (currentPosY > 7 || currentPosX > 7 || currentPosY < 0 || currentPosX < 0 || lenght == 15)
    {
      // проиграли начинаем заново
      directionX = 0;
      directionY = 0;
      lc.clearDisplay(0);
      currentPosX = 3;
      currentPosY = 3;
      Serial.println("All again");
      lenght = 2;
      lc.setLed(0, 3, 3, 1);
      frutGeneration();
      startFlag = 1;
    }
    if (fruitFlag)
      frutGeneration();
  }
}

/*
//! первый баг
 после движения влево змея может пойти вправо.
 после движения вверх змея может идти вниз

! второй баг
 фрукт может сгерерироваться на теле змеи //? после того как съели фрукт, новый не видно

! третий баг

*/
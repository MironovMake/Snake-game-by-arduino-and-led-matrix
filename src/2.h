#include "LedControl.h"
#include "binary.h"

// LedControl::LedControl(int dataPin, int clkPin, int csPin, int numDevices)
LedControl lc = LedControl(12, 11, 10, 1);
// скорость змейки
int speed = 300;
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
int buttonRight = 5;
int buttonLeft = 2;
int buttonUp = 3;
int buttonDown = 4;

void step()
{
  // текущее положение Х становится предыдущим

  // обговляем текущее положение Х,Y (делаем шаг)
  currentPosX = currentPosX + directionX;
  currentPosY = currentPosY + directionY;

  lc.setLed(0, currentPosY, currentPosX, 1);
  // сделали шаг
  lc.setLed(0, previousPosY, previousPosX, 0);
  previousPosX = currentPosX;
  previousPosY = currentPosY;
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
  lc.setLed(0, currentPosY, currentPosX, 1);
}

void loop()
{
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
    Serial.print("digitalRead(buttonDown)  ");
    Serial.println(digitalRead(buttonDown));
  }
  else if (digitalRead(buttonRight))
  {
    directionY = 0; // двигаемся вправо
    directionX = 1;
    Serial.print("digitalRead(buttonRight)  ");
    Serial.println(digitalRead(buttonRight));
  }
  else if (digitalRead(buttonLeft))
  {
    directionY = 0; // двигаемся влево
    directionX = -1;
    Serial.print("digitalRead(buttonLeft)  ");
    Serial.println(digitalRead(buttonLeft));
  }

  // раз в заданное время делаем шаг
  if (millis() - timer > speed && (directionY != 0 || directionX != 0))
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
      lc.setLed(0, currentPosY, currentPosX, 1);
      Serial.println("All again");
    }
  }
}

// работа с циклами
// генерировать случайные числа
// работа с дисплеем
//
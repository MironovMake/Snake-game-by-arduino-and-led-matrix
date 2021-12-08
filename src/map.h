#include "Arduino.h" // LedControl library is used for controlling a LED matrix. Find it using Library Manager or download zip here: https://github.com/wayoda/LedControl
int a[3][4] = {
    {0, 1, 2, 3}, /*  initializers for row indexed by 0 */
    {4, 5, 6, 7}, /*  initializers for row indexed by 1 */
    {8, 9, 0, 1}  /*  initializers for row indexed by 2 */
};

int mapp2[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}};

int length = 3;
int fruit[] = {1, 2};
int currentPosition[] = {3, 3};
int speed = 1000;
int directionX = 1;
int directionY = 0;
int buttonRight;
int buttonLeft;

void setup()
{
    Serial.begin(9600);
    pinMode(buttonRight, INPUT_PULLUP);
    pinMode(buttonLeft, INPUT_PULLUP);
}

void loop()
{
    currentPosition[0] += directionX;
    currentPosition[1] += directionY;
    Serial.println(currentPosition[0]);
    Serial.println(currentPosition[1]);
    delay(1000);
}
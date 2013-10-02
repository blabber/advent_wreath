/*-
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <tobias.rehbein@web.de> wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return.
 *                                                             Tobias Rehbein
 */

#include <SoftPWM.h>

#define FADETIME   20

int advent = 0;
// The pins used for the candles.
int candles[] = {
  A0, A1, A2, A3};

void setup()
{
  // Make sure to turn off the annoying PIN 13 LED.
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Set all candle pins to output.
  for (int i = 0; i <= 3; i++)
  {
    pinMode(candles[i], OUTPUT);
  }

  // Set PIN 8 to input and enable internal pull-up resistors.
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);

  // Turn on first candle.
  digitalWrite(candles[advent], HIGH);
  delay(1000);

  // While PIN 8 is shorted with ground turn another candle on every second.
  while (digitalRead(8) == LOW)
  {
    if (advent != 3)
      advent++;

    digitalWrite(candles[advent], HIGH);
    delay(1000);
  }

  // Finally, when PIN 8 is no longer shorted with ground setup PWM.
  SoftPWMBegin();
  SoftPWMSetFadeTime(ALL, FADETIME, FADETIME);

  // Finally seed RNG an enter main loop.
  randomSeed(analogRead(5));
}

void loop()
{
  // Let the candles flicker.
  for (int i = 0; i <= advent; i++)
  {
    SoftPWMSet(candles[i], random(255));
  }

  delay(2 * FADETIME);
}


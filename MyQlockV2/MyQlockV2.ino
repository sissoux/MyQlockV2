#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include "MyQlock.h"
#include "define.h"


Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);    // Declare the LED strip using Adafruit library

MyQlock Qlock = MyQlock(LED_COUNT, LED_STRIP_PIN, &strip);
uint16_t Time = 85;
void setup()
{
  // put your setup code here, to run once:
  Qlock.begin();
  Qlock.writeOutput();
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(2000);
  Time++;
  Qlock.Hour = (Time / 60) % 24;
  Qlock.Minute = Time % 60;
  Qlock.writeOutput();
}

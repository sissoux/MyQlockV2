#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include "MyQlock.h"
#include "define.h"
#include <Wire.h>
#include <DS1307RTC.h>
#include "Color.h"


Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);    // Declare the LED strip using Adafruit library

MyQlock Qlock = MyQlock(LED_COUNT, LED_STRIP_PIN, &strip);

elapsedMillis TimeRefreshTimer = 0;
#define TIME_REFRESH_RATE 500 //ms

elapsedMillis DisplayRefreshTimer = 0;
#define DISPLAY_REFRESH_RATE 50 //ms

elapsedMillis SerialRefreshTimer = 0;
#define SERIAL_REFRESH_RATE 10 //ms




void setup()
{
  Qlock.begin();
  InitRTC();
  UpdateTime(&Qlock.Hour, &Qlock.Minute);
  Qlock.writeOutput();
}

void loop()
{
  TaskManager();
}

void TaskManager()
{
  if (TimeRefreshTimer >= TIME_REFRESH_RATE)
  {
    TimeRefreshTimer = 0;
    UpdateTime(&Qlock.Hour, &Qlock.Minute);
  }

  if (DisplayRefreshTimer >= DISPLAY_REFRESH_RATE)
  {
    DisplayRefreshTimer = 0;
    Qlock.writeOutput();
  }
  
  if (SerialRefreshTimer >= SERIAL_REFRESH_RATE)
  {
    SerialRefreshTimer = 0;
    SerialCheck();
  }
}

void SerialCheck()
{
    if (Serial.available())
    {
      time_t t = processSyncMessage();
      if (t) 
      {
        RTC.set(t);   // set the RTC and the system time to the received value
        setTime(t);
      }
    }
    
}

void InitRTC()
{
  setSyncProvider(RTC.get);
  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");
  setSyncInterval(120);
}

void UpdateTime(uint8_t *Hours, uint8_t *Minutes)
{
  if (timeStatus() == timeSet)
  {
    time_t t = now();
    *Hours = (uint8_t)hour(t);
    *Minutes = (uint8_t)minute(t);
  }
}

unsigned long processSyncMessage()
{
  unsigned long pctime = 0L;
  if (Serial.find(TIME_HEADER))
  {
    pctime = Serial.parseInt();
  }
  return pctime;
}


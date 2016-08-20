#include "MyQlock.h"

MyQlock::MyQlock(uint16_t LED_Count, uint8_t Pin, Adafruit_NeoPixel *StripPtr) : CurrentColor(200, 1.0, 0.7)
{
  this->StripLenght = LED_Count;
  this->StripPin = Pin;
  this->Strip = StripPtr;
}



void MyQlock::begin(void)
{
  this->Strip->begin();
  for (uint8_t i = 0; i < StripLenght; i++)
  {
    Strip->setPixelColor(i, Strip->Color(0, 0, 0));
  }
  Strip->show();
  
}

uint32_t MyQlock::timeMaskUpdate(uint8_t H, uint8_t M)
{
  uint8_t hours = H % 13 + (H - 1) / 12 + (M >= 35);
  uint8_t Minutes = M / 5;
  uint8_t minutes = M % 5;
  if (H===23 && M>=35)
  {
    hours = 0;
  }
  if (H==12 && M>=35)
  {
    hours = 1;
  }
  return (uint32_t)1 << (17 + hours) | (uint32_t)1 << (5 + Minutes) | (uint32_t)1 << minutes;
}

void MyQlock::pixelStateUpdate(uint32_t TimeMask)
{
  for (uint8_t x = 0; x < COLUMN_COUNT; x++)
  {
    for (uint8_t y = 0; y < ROW_COUNT; y++)
    {
      this->PixelIsOn[y][x] = ((Mask[y][x] & TimeMask) > 0); //We check if current pixel corresponds to current Hour Mask
    }
  }
}


void MyQlock::writeOutput()
{
  pixelStateUpdate(timeMaskUpdate(Hour, Minute));

  for (uint8_t x = 0; x < COLUMN_COUNT; x++)
  {
    for (uint8_t y = 0; y < ROW_COUNT; y++)
    {
      if (PixelIsOn[y][x])
      {
        uint8_t Pixel = Mapping[y][x];
        if (Pixel < StripLenght) Strip->setPixelColor(Pixel, (uint8_t)(this->CurrentColor.r*255.0), (uint8_t)(this->CurrentColor.g*255.0), (uint8_t)(this->CurrentColor.b*255.0));
      }
      else
      {
        uint8_t Pixel = Mapping[y][x];
        if (Pixel < StripLenght) Strip->setPixelColor(Pixel, 0);
      }
    }
  }
  Strip->show();
}









































// Fill the dots one after the other with a color
void MyQlock::colorWipe(uint32_t c, uint8_t wait) {

#ifdef FANCY_START
  colorWipe(strip.Color(0, 0, 255), 15); // Blue
  colorWipe(strip.Color(0, 0, 0), 15); // Blue
  rainbow(1);
  rainbow(1);
  rainbow(1);
#endif
  for (uint16_t i = 0; i < Strip->numPixels(); i++) {
    Strip->setPixelColor(i, c);
    Strip->show();
    delay(wait);
  }
}

void MyQlock::rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < Strip->numPixels(); i++) {
      Strip->setPixelColor(i, Wheel((i + j) & 255));
    }
    Strip->show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t MyQlock::Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return Strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return Strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return Strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


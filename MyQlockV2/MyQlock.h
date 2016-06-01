#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include "Color.h"

#ifndef Qlock_h
#define Qlock_h

#define ROW_COUNT 12
#define COLUMN_COUNT 13


class MyQlock
{
  public:
    Color CurrentColor;//(120, 1, 1);
    MyQlock(uint16_t LED_Count, uint8_t Pin, Adafruit_NeoPixel *StripPointer);
    Adafruit_NeoPixel *Strip = NULL;
    uint16_t StripLenght = 0;
    uint8_t StripPin = 0;
    uint8_t Hour = 0;
    uint8_t Minute = 4;
    void begin();
    void colorWipe(uint32_t c, uint8_t wait);
    void rainbow(uint8_t wait);
    uint32_t timeMaskUpdate(uint8_t H, uint8_t M);
    void pixelStateUpdate(uint32_t TimeMask);
    void writeOutput();

    /*double R = 0;
      double G = 0;
      double B = 0;
      uint32_t Strip = 0;
      double h = 0;
      double s = 0;
      double v = 0;*/

  private:
    uint32_t Wheel(byte WheelPos);

    // Mapping is used to convert Pixel coordinates {Col;Row} to pixel strip number. if value = 150 ==> No LED
    uint8_t Mapping[ROW_COUNT][COLUMN_COUNT] =
    {
      {113, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 101},
      {150, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 150},
      {150, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 150},
      {150, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 150},
      {150, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 150},
      {150, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 150},
      {150, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 150},
      {150, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 150},
      {150, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 150},
      {150, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 150},
      {150, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 150},
      {0, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 12}
    };

    // Mask is used to determine if Pixel {Col;Row} shall be lit at a particular hour and minute combination.
    uint32_t Mask[ROW_COUNT][COLUMN_COUNT] =
    {
      {16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30},
      {0, 1073610752, 1073610752, 0, 1073610752, 1073610752, 1073610752, 0, 4194304, 4194304, 4194304, 4194304, 0},
      {0, 2097152, 2097152, 2097152, 2097152, 2097152, 2097152, 1048576, 1048576, 1048576, 1048576, 1048576, 0},
      {0, 67108864, 67108864, 67108864, 67108864, 536870912, 0, 134217728, 25165824, 16777216, 16777216, 16777216, 0},
      {0, 262144, 262144, 262144, 131072, 537001984, 131072, 131072, 142737408, 131072, 0, 0, 0},
      {0, 268435456, 268435456, 268435456, 268435456, 537395200, 524288, 524288, 8912896, 134217728, 0, 0, 0},
      {0, 33554432, 33554432, 33554432, 33554432, 536870912, 536608768, 536608768, 536608768, 536608768, 536608768, 536346624, 0},
      {0, 126976, 126976, 126976, 126976, 126976, 0, 16384, 16384, 32896, 32896, 32896, 0},
      {0, 256, 256, 0, 16640, 16640, 16640, 16640, 16640, 0, 0, 0, 0},
      {0, 0, 13824, 13824, 13824, 13824, 13824, 5120, 70720, 70720, 70720, 70720, 0},
      {0, 2048, 2048, 0, 2048, 2048, 2048, 2048, 2048, 0, 0, 0, 0},
      {24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28}
    };

    uint8_t PixelIsOn[ROW_COUNT][COLUMN_COUNT];


    /*void rgb2hsv(void);
      void hsv2rgb(void);*/
};


#endif

#include "Arduino.h"

#ifndef color_h
#define color_h


class Color
{
  public:
    double R = 0;
    double G = 0;
    double B = 0;
    uint32_t Strip = 0;
    double h = 0;
    double s = 0;
    double v = 0;

  private:
    void rgb2hsv(void);
    void hsv2rgb(void);
};


#endif

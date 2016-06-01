#include "Arduino.h"

#ifndef color_h
#define color_h


class Color
{
  public:
    uint32_t StripColor = 0;
    
    double r = 0;
    double g = 0;
    double b = 0;
    
    double h = 0;
    double s = 0;
    double v = 0;
    
    Color(double h, double s, double v);

  public:
    void convertToRGB();
    //void convertToHSV()
};


#endif

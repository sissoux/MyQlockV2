#include "Color.h"


Color::Color(double h, double s, double v)
{
  this->h = h;
  this->s = s;
  this->v = v;
  convertToRGB();
}
 /*
Color::hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
            // s = 0, v is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}*/


void Color::convertToRGB()
{
    double      hh, p, q, t, ff;
    long        i;

    if(this->s <= 0.0) {       // < is bogus, just shuts up warnings
        this->r = this->v;
        this->g = this->v;
        this->b = this->v;
        return;
    }
    hh = this->h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = this->v * (1.0 - this->s);
    q = this->v * (1.0 - (this->s * ff));
    t = this->v * (1.0 - (this->s * (1.0 - ff)));

    switch(i) {
    case 0:
        this->r = this->v;
        this->g = t;
        this->b = p;
        break;
    case 1:
        this->r = q;
        this->g = this->v;
        this->b = p;
        break;
    case 2:
        this->r = p;
        this->g = this->v;
        this->b = t;
        break;

    case 3:
        this->r = p;
        this->g = q;
        this->b = this->v;
        break;
    case 4:
        this->r = t;
        this->g = p;
        this->b = this->v;
        break;
    case 5:
    default:
        this->r = this->v;
        this->g = p;
        this->b = q;
        break;
    }
    return;     
}


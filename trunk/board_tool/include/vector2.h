#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <cmath>

class Vector2
{
public:
    Vector2() {}
    
    double length() {
        return sqrt( x*x + y*y );   
    }
    
    void normalize() {
        double len = length();
        x /= len;
        y /= len;
    }
    
    Vector2 & operator*=( double v ) {
        x *= v;
        y *= v;
        return *this;
    }
    
    double x, y;
};

#endif 

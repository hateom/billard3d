/***************************************************************************
 *   Copyright (C) 2007 by Tomasz Huczek                                      *
 *   tomasz.huczek@gmail.com                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <cmath>
#include <iostream>
#include "bvector.h"

bVector::bVector()
{
}

bVector::bVector( double ix, double iy ) : x(ix), y(iy)
{
}

bVector::bVector( const bVector & rhs ) : x(rhs.x), y(rhs.y)
{
}

bVector::bVector( bVector * ptr )
{
    x = ptr->x;
    y = ptr->y;
}

double bVector::length()
{
    return sqrt( x*x + y*y );
}

bVector & bVector::operator +=( double v )
{
    x += v;
    y += v;
    return *this;
}

bVector & bVector::operator +=( const bVector & v )
{
    x += v.x;
    y += v.y;
    return *this;
}
    
bVector & bVector::operator -=( double v )
{
    x -= v;
    y -= v;
    return *this;
}

bVector & bVector::operator -=( const bVector & v )
{
    x -= v.x;
    y -= v.y;
    return *this;
}
    
bVector & bVector::operator *=( double v )
{
    x *= v;
    y *= v;
    return *this;
}
    
bVector & bVector::operator /=( double v )
{
    x /= v;
    y /= v;
    return *this;
}
    
bVector bVector::operator+( double v )
{
    bVector vec( *this );
    vec.x += v;
    vec.y += v;
    return vec;
}

bVector bVector::operator+( const bVector & v )
{
    bVector vec( *this );
    vec.x += v.x;
    vec.y += v.y;
    return vec;
}

bVector bVector::operator-( double v )
{
    bVector vec( *this );
    vec.x -= v;
    vec.y -= v;
    return vec;
}

bVector bVector::operator-( const bVector & v )
{
    bVector vec( *this );
    vec.x -= v.x;
    vec.y -= v.y;
    return vec;
}

bVector bVector::operator*( double v )
{
    bVector vec( *this );
    vec.x *= v;
    vec.y *= v;
    return vec;
}

bVector bVector::operator/( double v )
{
    bVector vec( *this );
    vec.x /= v;
    vec.y /= v;
    return vec;
}

bVector bVector::normal()
{
    bVector vec( *this );
    double len = length();
    if( len == 0.0 ) len = 1.0;
    vec.x /= len;
    vec.y /= len;
    return vec;
}

bVector & bVector::normalize()
{
    double len = length();
    if( len == 0.0 ) len = 1.0;
    x /= len;
    y /= len;
    return *this;
}

double bVector::distance( bVector & vec )
{
    return sqrt( (x-vec.x)*(x-vec.x) + (y-vec.y)*(y-vec.y) );
}
/*
bVector & bVector::operator=( bVector & rhs )
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}
*
bVector & bVector::operator=( bVector rhs )
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}
*/
bVector bVector::operator=( bVector rhs )
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

bVector & bVector::operator=( double val )
{
    x = y = val;
    return *this;
}

std::ostream & operator<<(std::ostream & out, const bVector & v)
{
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}
    
double bVector::cross( bVector & v )
{
    return x*v.y-y*v.x;
}

double DotProduct( bVector & b1, bVector & b2 )
{
    return b1.x*b2.x + b1.y*b2.y;
}

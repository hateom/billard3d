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
#include "bvector3.h"

#define EPS 0.0000001
#define BABS( X ) (((X)<0.0)?((-1.0)*(X)):(X))

bVector3::bVector3()
{
}

bVector3::bVector3( double ix, double iy, double iz ) : x(ix), y(iy), z(iz)
{
}

bVector3::bVector3( const bVector3 & rhs ) : x(rhs.x), y(rhs.y), z(rhs.z)
{
}

bVector3::bVector3( bVector3 * ptr )
{
    x = ptr->x;
    y = ptr->y;
    z = ptr->z;
}

double bVector3::length()
{
    return sqrt( x*x + y*y + z*z );
}

bVector3 & bVector3::operator +=( double v )
{
    x += v;
    y += v;
    z += v;
    return *this;
}

bVector3 & bVector3::operator +=( const bVector3 & v )
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
    
bVector3 & bVector3::operator -=( double v )
{
    x -= v;
    y -= v;
    z -= v;
    return *this;
}

bVector3 & bVector3::operator -=( const bVector3 & v )
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}
    
bVector3 & bVector3::operator *=( double v )
{
    x *= v;
    y *= v;
    z *= v;
    return *this;
}
    
bVector3 & bVector3::operator /=( double v )
{
    x /= v;
    y /= v;
    z /= v;
    return *this;
}
    
bVector3 bVector3::operator+( double v )
{
    bVector3 vec( *this );
    vec.x += v;
    vec.y += v;
    vec.z += v;
    return vec;
}

bVector3 bVector3::operator+( const bVector3 & v )
{
    bVector3 vec( *this );
    vec.x += v.x;
    vec.y += v.y;
    vec.z += v.z;
    return vec;
}

bVector3 bVector3::operator-( double v )
{
    bVector3 vec( *this );
    vec.x -= v;
    vec.y -= v;
    vec.z -= v;
    return vec;
}

bVector3 bVector3::operator-( const bVector3 & v )
{
    bVector3 vec( *this );
    vec.x -= v.x;
    vec.y -= v.y;
    vec.z -= v.z;
    return vec;
}

bVector3 bVector3::operator*( double v )
{
    bVector3 vec( *this );
    vec.x *= v;
    vec.y *= v;
    vec.z *= v;
    return vec;
}

bVector3 bVector3::operator/( double v )
{
    bVector3 vec( *this );
    vec.x /= v;
    vec.y /= v;
    vec.z /= v;
    return vec;
}

bVector3 bVector3::normal()
{
    bVector3 vec( *this );
    double len = length();
    if( len == 0.0 ) { len = 1.0; vec.zero(); }
    vec.x /= len;
    vec.y /= len;
    vec.z /= len;
    return vec;
}

bVector3 & bVector3::normalize()
{
    double len = length();
    if( len == 0.0 ) { len = 1.0; zero(); }
    x /= len;
    y /= len;
    z /= len;
    return *this;
}

double bVector3::distance( bVector3 & vec )
{
    return sqrt( (x-vec.x)*(x-vec.x) + (y-vec.y)*(y-vec.y) + (z-vec.z)*(z-vec.z) );
}

bVector3 bVector3::operator=( bVector3 rhs )
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

bVector3 & bVector3::operator=( double val )
{
    x = y = z = val;
    return *this;
}

std::ostream & operator<<(std::ostream & out, const bVector3 & v)
{
    out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return out;
}
    
double bVector3::cross( bVector3 & v )
{
    return x*v.y-y*v.x;
}

double DotProduct( bVector3 & b1, bVector3 & b2 )
{
    return b1.x*b2.x + b1.y*b2.y + b1.z*b2.z;
}

void bVector3::ifzero()
{
    if( BABS(x) < EPS ) { 
        x = 0.0; 
    }
    
    if( BABS(y) < EPS ) { 
        y = 0.0; 
    }
    
    if( BABS(y) < EPS ) { 
        z = 0.0; 
    }
}

bVector3::bVector3(bVector vec) : x(vec.x), y(0.0), z(vec.y)
{
}

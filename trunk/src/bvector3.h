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

#ifndef BVECTOR3_H
#define BVECTOR3_H

#include <iostream>
#include "bvector.h"

/**
    @brief 3D Vector Class
    Defines mathematical two dimension vector
	@author Tomasz Huczek <tomasz.huczek@gmail.com>
*/
class bVector3
{
public:
    bVector3();
    bVector3( bVector vec );
    bVector3( double x, double y, double z );
    bVector3( const bVector3 & rhs );
    bVector3( bVector3 * ptr );
    ~bVector3() {}
    
    bVector3 operator=( bVector3 rhs );
    bVector3 & operator=( double val );

    double length();
    
    bVector3 & operator +=( double v );
    bVector3 & operator +=( const bVector3 & v );
    
    bVector3 & operator -=( double v );
    bVector3 & operator -=( const bVector3 & v );
    
    bVector3 & operator *=( double v );
    bVector3 & operator /=( double v );
    
    bVector3 operator+( double v );
    bVector3 operator+( const bVector3 & v );
    
    bVector3 operator-( double v );
    bVector3 operator-( const bVector3 & v );
    
    bVector3 operator*( double v );
    bVector3 operator/( double v );
    
    bVector3 normal();
    bVector3 & normalize();
    
    double distance( bVector3 & vec );
    double cross( bVector3 & vec );
    void zero() { x = y = 0.0; }
    
    void ifzero();
    
public:
    double x, y, z;
};

//---------------------------------------------------------------------------------------------

double DotProduct( bVector3 & b1, bVector3 & b2 );
std::ostream& operator<<( std::ostream& out, const bVector3 & v );

//---------------------------------------------------------------------------------------------

#endif

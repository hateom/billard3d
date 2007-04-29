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

#ifndef BVECTOR_H
#define BVECTOR_H

//---------------------------------------------------------------------------------------------

#include <iostream>

//---------------------------------------------------------------------------------------------

/**
	@author Tomasz Huczek <tomasz.huczek@gmail.com>
*/
class bVector{
public:
    bVector();
    bVector( double x, double y );
    bVector( const bVector & rhs );
    bVector( bVector * ptr );
    ~bVector() {}
    
    //bVector & operator=( bVector rhs );
    bVector operator=( bVector rhs );
    bVector & operator=( double val );

    double length();
    
    bVector & operator +=( double v );
    bVector & operator +=( const bVector & v );
    
    bVector & operator -=( double v );
    bVector & operator -=( const bVector & v );
    
    bVector & operator *=( double v );
    bVector & operator /=( double v );
    
    bVector operator+( double v );
    bVector operator+( const bVector & v );
    
    bVector operator-( double v );
    bVector operator-( const bVector & v );
    
    bVector operator*( double v );
    bVector operator/( double v );
    
    bVector normal();
    bVector & normalize();
    
    double distance( bVector & vec );
    double cross( bVector & vec );
    void zero() { x = y = 0.0; }
    
    void ifzero();
    
public:
    double x, y;
};

//---------------------------------------------------------------------------------------------

double DotProduct( bVector & b1, bVector & b2 );
std::ostream& operator<<( std::ostream& out, const bVector & v );

//---------------------------------------------------------------------------------------------

#endif

/***************************************************************************
 *   Copyright (C) 2007 by                                       *
 *                                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include <GL/gl.h>
#include <cmath>
#include "bband.h"

#define BABS( VAL ) ((VAL)<0.0)?(-(VAL)):(VAL)

bBand::bBand()
{
}


bBand::~bBand()
{
}

void bBand::draw()
{
    glColor3f( 1.0f, 1.0f, 1.0f );
    glBegin( GL_LINES );
        glVertex2d( p1.x, p1.y );
        glVertex2d( p2.x, p2.y );
    glEnd();
}

bBand::bBand(bVector _p1, bVector _p2) : p1(_p1), p2(_p2)
{
}

double bBand::distance( bVector pt )
{
    double A, B, C;
    
    if( p2.x == p1.x ) {
        A = 0.0;
    } else {
        A = (p2.y-p1.y)/(p2.x-p1.x);
    }
    
    B = -1.0;
    C = p1.y - A*p1.x;
    
    return BABS( A*pt.x + B*pt.y + C) / sqrt( A*A + B*B );
}

bool bBand::is_within(bVector pt, double rad)
{
    double d = distance( pt );
    if( d > rad ) return false;
    
    double p12d = (p2-p1).length();
    double p1d = (pt-p1).length();
    double p2d = (pt-p2).length();
    
    double x1 = sqrt(p1d*p1d-d*d);
    double x2 = sqrt(p2d*p2d-d*d);
    
    if( (x1 <= p12d && x2 <= p12d) || (p1d <= rad || p2d <= rad)) return true;
    
    return false;
}



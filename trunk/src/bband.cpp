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

#include "bsdl.h"
#include <cmath>
#include "bband.h"
#include "blogger.h"

#define BABS( VAL ) ((VAL)<0.0)?(-(VAL)):(VAL)

bBand::bBand()
{
}


bBand::~bBand()
{
}

void bBand::draw()
{
    glDisable( GL_CULL_FACE );
    glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 0.4f, 0.4f, 1.0f );
        glVertex3d( p1.x, 1.0, p1.y );
        glColor3f( 0.1f, 0.1f, 0.5f );
        glVertex3d( p1.x, 0.0, p1.y );
        glColor3f( 0.4f, 0.4f, 1.0f );
        glVertex3d( p2.x, 1.0, p2.y );
        glColor3f( 0.1f, 0.1f, 0.5f );
        glVertex3d( p2.x, 0.0, p2.y );
    glEnd();
    glEnable( GL_CULL_FACE );
}

bBand::bBand(bVector _p1, bVector _p2) : p1(_p1), p2(_p2)
{
    recalc();
}

double bBand::distance( bVector pt ) const
{
    return (BABS( a*pt.x + b*pt.y + c)) / det;
}

bBand::band_piece bBand::is_within(bVector pt, double rad)
{
    double d = distance( pt );
    if( d > rad ) return bBand::bNone;
    
    double p12d = (p2-p1).length();
    double p12ds = p12d*p12d;
    double p1d = (pt-p1).length();
    double p2d = (pt-p2).length();
    double p1ds = p1d*p1d;
    double p2ds = p2d*p2d;
    double x1 = p1ds-d*d;
    double x2 = p2ds-d*d;
    
    if( x1 <= p12ds && x2 <= p12ds ) return bBand::bSide;
    if( p1d <= rad ) return bBand::bEdge1;
    if( p2d <= rad ) return bBand::bEdge2;
    
    return bBand::bNone;
}

void bBand::recalc()
{
    if( p2.x == p1.x ) {
        a = 0.0;
    } else {
        a = (p2.y-p1.y)/(p2.x-p1.x);
    }
    
    b = -1.0;
    c = p1.y - a*p1.x;
    det = sqrt( a*a + b*b );
}

void bBand::set_points(bVector ip1, bVector ip2)
{
    p1 = ip1;
    p2 = ip2;
    recalc();
}

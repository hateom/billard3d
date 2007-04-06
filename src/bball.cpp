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

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include "bball.h"

#define G_PI 3.1415

bBall::bBall() : f(false)
{
    acc.zero();
    vel.zero();
    pos.zero();
    mass = 1.0;
}

bBall::~bBall()
{
}

void bBall::draw()
{
    int rnum = 32;
    double nrad = (2.0*G_PI)/(double)rnum;
    double rad = 0.0;
    
    glBegin( GL_TRIANGLE_FAN );
        glColor3f( r, g, b );
        if( f ) {
            glColor3f( 1.0f, 1.0f, 1.0f );    
        }
        glVertex2d( pos.x, pos.y );
        glColor3f( r/5.0, g/5.0, b/5.0 );
        glVertex2d( pos.x + radius*cos(0.0), pos.y + radius*sin(0.0) );
        for( int i=0; i<rnum; ++i ) {
            rad -= nrad;
            glVertex2d( pos.x + radius*cos(rad), pos.y + radius*sin(rad) );
        }
    glEnd();
}

void bBall::process( double fps_factor )
{
//    vel += acc * fps_factor;
    pos += vel * fps_factor;
}

void bBall::unprocess( double fps_factor )
{
    pos -= vel * fps_factor;
//    vel -= acc * fps_factor;
}

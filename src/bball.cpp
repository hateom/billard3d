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
#include "bassert.h"

#define G_PI 3.1415

#define EPS 0.01

bBall::bBall() : t_vel_f(false)
{
    acc.zero();
    vel.zero();
    pos.zero();
    t_vel.zero();
    mass = 1.0;
    r = g = b = 0.9f;
    acc.y = 300.0;
}

bBall::bBall(bVector ip, bVector iv, bVector ia, 
             double irad, double imass, float ir, float ig, float ib) :
        pos(ip), vel(iv), acc(ia), radius(irad), mass(imass), 
        r(ir), g(ig), b(ib), t_vel_f(false)
{
    t_vel.zero();
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
    vel += acc * fps_factor;
    pos += vel * fps_factor;
}

void bBall::unprocess( double fps_factor )
{
    pos -= vel * fps_factor;
    vel -= acc * fps_factor;
}

bVector bBall::collision(bBall * b)
{
    static bVector n;
    static double a1, a2, p;
    
    BASSERT( b != NULL );
    
    n = pos - b->pos;
    n.normalize();
    
    a1 = DotProduct( vel, n );
    a2 = DotProduct( b->vel, n );
    p = ( 2.0 * ( a1- a2 )) / ( mass + b->mass );
        
    bVector v1 = vel - n*p*b->mass;
    
    return v1;
}

bVector bBall::collision(bBand * b)
{
    bVector n(b->p2 - b->p1), v(vel);
    double scal;
    n.normalize();
   
    scal = DotProduct( v, n );
    v *= -1.0;
    
    return ( v + n*scal*2.0 );
}

bool bBall::collides(bBall * b)
{
    BASSERT( b != NULL );
    
    if( pos.distance( b->pos ) <= ( radius + b->radius ) ) {
        return true;
    }
    
    return false;
}

bVector bBall::collision(bBand * b, bBand::band_piece edge)
{
    BASSERT( b != NULL );
    BASSERT( edge == bBand::bEdge1 || edge == bBand::bEdge2 );
    
    bVector edg;
    if( edge == bBand::bEdge1 ) {
        edg = b->p1;
    } else {
        edg = b->p2;
    }
    bVector n(pos - edg), v(vel);
    double scal;
    n.normalize();
    double temp;
    temp = n.x;
    n.x = n.y;
    n.y = -temp;
   
    scal = DotProduct( v, n );
    v *= -1.0;
    
    return ( v + n*scal*2.0 );
}

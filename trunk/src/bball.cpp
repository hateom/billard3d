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

bBall::bBall( int inum_balls, int inum_bands ) : 
        num_balls(inum_balls), num_bands(inum_bands), num_collisions(0), num_band_collisions(0),
        t_vel_f(false)
{
    acc.zero();
    vel.zero();
    pos.zero();
    t_vel.zero();
    mass = 1.0;
    r = g = b = 0.9f;
    acc.y = 300.0;
    
    collisions = new int[num_balls];
    band_collisions = new int[num_bands];
}

bBall::bBall(int inum_balls, int inum_bands, bVector ip, bVector iv, bVector ia, 
             double irad, double imass, float ir, float ig, float ib) :
        pos(ip), vel(iv), acc(ia), radius(irad), mass(imass), 
        r(ir), g(ig), b(ib), num_balls(inum_balls), num_bands(inum_bands), 
        num_collisions(0), num_band_collisions(0), t_vel_f(false)
{
    collisions = new int[num_balls];
    band_collisions = new int[num_bands];
    t_vel.zero();
}

bBall::~bBall()
{
    delete [] collisions;
    collisions = NULL;
    delete [] band_collisions;
    band_collisions = NULL;
}

void bBall::draw()
{
    int rnum = 32;
    double nrad = (2.0*G_PI)/(double)rnum;
    double rad = 0.0;
    
    glBegin( GL_TRIANGLE_FAN );
        glColor3f( r, g, b );
        if( has_collisions() ) {
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
    vel += acc * fps_factor;
    pos += vel * fps_factor;
    vel *= 0.999999;
}

void bBall::unprocess( double fps_factor )
{
    vel *= 1.000001;
    pos -= vel * fps_factor;
    vel -= acc * fps_factor;
}

void bBall::set_collision(int ball)
{
    BASSERT( num_collisions < num_balls );
    
    collisions[num_collisions] = ball;
    num_collisions++;
}

bool bBall::is_collision(int ball)
{
    int temp = 0;
    while( temp < num_collisions ) {
        if( collisions[temp] == ball ) {
            return true;
        }
        temp++;
    }
    
    return false;
}

void bBall::clear_collisions()
{
    num_collisions = 0;
    num_band_collisions = 0;
}

int bBall::get_collisions_num()
{
    return num_collisions;
}

int bBall::get_collision( int num )
{
    BASSERT( num < num_collisions );
    return collisions[num];
}

bool bBall::has_collisions()
{
    return num_collisions > 0 || num_band_collisions > 0;
}

int bBall::get_band_collisions_num()
{
    return num_band_collisions;
}

int bBall::get_band_collision(int num)
{
    BASSERT( num < num_band_collisions );
    return band_collisions[num];
}

void bBall::set_band_collision(int band)
{
    BASSERT( num_band_collisions < num_bands );
    
    band_collisions[num_band_collisions] = band;
    num_band_collisions++;
}

bool bBall::is_band_collision(int band)
{
    int temp = 0;
    while( temp < num_band_collisions ) {
        if( band_collisions[temp] == band ) {
            return true;
        }
        temp++;
    }
    
    return false;
}


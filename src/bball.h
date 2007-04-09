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

#ifndef BBALL_H
#define BBALL_H

#include "bvector.h"

/**
	@author Tomasz Huczek <tomasz.huczek@gmail.com>
*/
class bBall{
public:
    bBall( int num_balls );
    bBall( int num_balls, 
           bVector pos, bVector v, bVector a, double radius, 
           double mass = 1.0, float r = 1.0f, float g = 1.0f, float b = 1.0f );
    ~bBall();
    
    void draw();
    void process( double fps_factor );
    void unprocess( double fps_factor );
    
   
    void set_collision( int ball );
    bool is_collision( int ball );
    bool has_collisions();
    void clear_collisions();
    int  get_collisions_num();
    int  get_collision( int num );
    
    void set_v( bVector v ) { t_vel_f = true; t_vel = v; }
    void commit_v() { if( t_vel_f ) { vel = t_vel; t_vel_f = false; } }

public:
    bVector pos, vel, acc;
    double radius;
    double mass;
    
    float r,g,b;
    
    int * collisions;
    int num_balls;
    int num_collisions;
    
    bVector t_vel;
    bool t_vel_f;
};

#endif

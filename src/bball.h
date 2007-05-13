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

#include "bband.h"
#include "bvector.h"
#include "bgl.h"
#include "GLquat.h"

/**
    @brief Ball object
    This class represents a ball, and defines some useful methods.
	@author Tomasz Huczek <tomasz.huczek@gmail.com>
*/
class bBall
{
public:
    bBall();
    bBall( bVector pos, bVector v, bVector a, double radius, 
           double mass = 1.0, float r = 1.0f, float g = 1.0f, float b = 1.0f );
    ~bBall();
    
    /// draws ball
    void draw();
    
    /// draws ball shadow
    void draw_shadow();
    
    /// apply physical calculations of the velocity, 
    /// position and acceleration
    void process( double fps_factor );
    
    /// undo @b process calculations
    void unprocess( double fps_factor );
    
    /// @param force means how many collisions occured
    void report_collision( int force );
    
    /// save the temporary velocity
    void set_v( bVector v ) { t_vel_f = true; t_vel = v; }
    
    /// apply temporary velocity - overwrites current
    void commit_v();
    
    /// @returns velocity vector after collision with another ball
    bVector collision( bBall * b );
    
    /// @returns velocity vector after collision with band
    bVector collision( bBand * b );
    
    /// @returns velocity vector after collision with band edge
    bVector collision( bBand * b, bBand::band_piece edge );
    
    /// check whether collision occured
    bool    collides( bBall * b );

public:
    bVector pos,     ///< position vector
            vel,     ///< velocity vector
            acc,     ///< acceleration vector
			phi;	 ///< rotation vector
    
    double lphi;
    double radius;   ///< radius of the ball
    double mass;     ///< mass of the ball
    double blphi;
    
    GL_QUAT qrot, dqrot;
    float   rotmat[4][4];
    
    float r,         ///< red component of the color value
          g,         ///< green component of the color value
          b;         ///< blue component of the color value
    
    bVector t_vel;   ///< temporary velocity
    bool    t_vel_f; ///< is temporary velocity set
    
    GLUquadricObj * sphere_obj;
};

//---------------------------------------------------------------------------------------------

#endif

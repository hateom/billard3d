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
#include "bball.h"
#include "bassert.h"
#include "btrace.h"
#include "bsdl.h"
#include "bquaternion.h"

#define COL_FACTOR 0.2

#define G_PI 3.1415

#define EPS 0.01

bBall::bBall() : t_vel_f(false)
{
    acc.zero();
    vel.zero();
    pos.zero();
	phi.zero();
    t_vel.zero();
    mass = 1.0;
    r = g = b = 0.9f;
    acc.y = 300.0;
    sphere_obj = gluNewQuadric();
	gluQuadricNormals( sphere_obj, GL_SMOOTH );
	gluQuadricTexture( sphere_obj, GL_TRUE );
}

bBall::bBall(bVector ip, bVector iv, bVector ia, 
             double irad, double imass, float ir, float ig, float ib) :
        pos(ip), vel(iv), acc(ia), radius(irad), mass(imass), 
        r(ir), g(ig), b(ib), t_vel_f(false)
{
    t_vel.zero();
    sphere_obj = gluNewQuadric();
}

bBall::~bBall()
{
}

void bBall::draw()
{
    double mat[16];
    bQuaternion q, q1(-1.0,0.0,0.0,(phi.x*3.1415*2.0)/180.0), q2(0.0,0.0,-1.0,(phi.y*3.1415*2.0)/180.0);
    q = q1 * q2;
    q.create_matrix(mat);
    glPushMatrix();
        glMultMatrixd(mat);
		glTranslated( pos.x, 0.0, pos.y );
		glColor3f( r, g, b );
		gluSphere(sphere_obj, radius, 16, 16);
    glPopMatrix();
}

void bBall::process( double fps_factor )
{
    guard(bBall::process);
    
    static double mi = 0.005;
    double ta = ((mi*10.0)/radius)*fps_factor;
    
    if( vel.length() < ta )
    {
        vel.zero();
    }
    else
    {
        vel -= vel.normal()*ta;
    }
    
    vel += acc * fps_factor;
    pos += vel * fps_factor;

	phi.x += ( vel.x / radius ) * fps_factor;
	phi.y += ( vel.y / radius ) * fps_factor;
    
    unguard;
}

void bBall::unprocess( double fps_factor )
{
	phi.x -= ( vel.x / radius ) * fps_factor;
	phi.y -= ( vel.y / radius ) * fps_factor;

    pos -= vel * fps_factor;
    vel -= acc * fps_factor;
}

bVector bBall::collision(bBall * b)
{
    guard(bBall::collision);
    
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
    
    unguard;
}

bVector bBall::collision(bBand * b)
{
    guard(bBall::collision);
    
    bVector n(b->get_p2() - b->get_p1()), v(vel);
    double scal;
    n.normalize();
   
    scal = DotProduct( v, n );
    v *= -1.0;
    
    return ( v + n*scal*2.0 );
    
    unguard;
}

bool bBall::collides(bBall * b)
{
    guard(bBall::collides);
    
    BASSERT( b != NULL );
    
    if( pos.distance( b->pos ) <= ( radius + b->radius ) ) {
        return true;
    }
    
    return false;
    
    unguard;
}

bVector bBall::collision(bBand * b, bBand::band_piece edge)
{
    guard(bBall::collision);
    
    BASSERT( b != NULL );
    BASSERT( edge == bBand::bEdge1 || edge == bBand::bEdge2 );
    
    bVector edg;
    if( edge == bBand::bEdge1 ) {
        edg = b->get_p1();
    } else {
        edg = b->get_p2();
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
    
    unguard;
}

void bBall::report_collision(int type)
{
    double dtype = (double)type;
    t_vel.x -= t_vel.x*(dtype*COL_FACTOR);
    t_vel.y -= t_vel.y*(dtype*COL_FACTOR);
}

void bBall::commit_v()
{
    if( t_vel_f ) { 
        vel = t_vel;
        vel.ifzero();
        t_vel_f = false; 
    } 
}

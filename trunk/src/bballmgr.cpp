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

#include <iostream>
#include "bballmgr.h"

bBallMgr::bBallMgr() : size(0), ball(NULL)
{
}


bBallMgr::~bBallMgr()
{
    release();
}

bool bBallMgr::create()
{
    size = 4;
    ball = new bBall[size];
    
    ball[0].pos.x  = 100.0;
    ball[0].pos.y  = 100.0;
    ball[0].radius = 70.0;
    ball[0].vel.x  = 0.4;
    ball[0].vel.y  = -0.4;
    ball[0].r = 1.0f; ball[0].g = 0.5f; ball[0].b = 0.5f;
    ball[0].mass = 5.0;
    
    ball[1].pos.x  = 500.0;
    ball[1].pos.y  = 100.0;
    ball[1].radius = 50.0;
    ball[1].vel.x  = 0.4;
    ball[1].vel.y  = -0.4;
    ball[1].r = 0.5f; ball[1].g = 1.0f; ball[1].b = 0.5f;
    
    ball[2].pos.x  = 100.0;
    ball[2].pos.y  = 400.0;
    ball[2].radius = 50.0;
    ball[2].vel.x  = -0.4;
    ball[2].vel.y  = -0.4;
    ball[2].r = 0.5f; ball[2].g = 0.5f; ball[2].b = 1.0f;
    
    ball[3].pos.x  = 500.0;
    ball[3].pos.y  = 400.0;
    ball[3].radius = 50.0;
    ball[3].vel.x  = -0.4;
    ball[3].vel.y  = 0.4;
    ball[3].r = 1.0f; ball[3].g = 0.5f; ball[3].b = 1.0f;
    
    return true;
}

void bBallMgr::release()
{
    delete [] ball;
    ball = NULL;
    size = 0;
}

void bBallMgr::draw()
{
    int bcol;
    
    for( int i=0; i<size; ++i )
    {
        ball[i].process();
        if( ( bcol = border_col( &ball[i] ) ) != 0 )
        {
            ball[i].unprocess();
            if( bcol == 1 ) // x-border
            {
                ball[i].vel.x *= -1.0;
            }
            else // y-border
            {
                ball[i].vel.y *= -1.0;
            }
        }
        for( int j=0; j<size; ++j )
        {
            if( i == j || ball[i].isf() ) continue;
            if( ball_col( &ball[i], &ball[j] ) )
            {
                ball[i].unprocess();
                ball[j].unprocess();
                
                ball[i].setf( true );
                ball[j].setf( true );
                
                collide( &ball[i], &ball[j] );
            }
        }
        ball[i].draw();
        ball[i].setf( false );
    }
}

void bBallMgr::collide( bBall * b1, bBall * b2 )
{
    static bVector n;
    static double a1, a2, p;
    
    n = b1->pos - b2->pos;
    n.normalize();
    
    a1 = DotProduct( b1->vel, n );
    a2 = DotProduct( b2->vel, n );
    p = ( 2.0 * ( a1- a2 )) / ( b1->mass + b2->mass );
        
    bVector v1 = b1->vel - n*p*b2->mass;
    bVector v2 = b2->vel + n*p*b1->mass;
    
    b1->vel = v1;
    b2->vel = v2;
}

int bBallMgr::ball_col( bBall * b1, bBall * b2 )
{
    if( b1->pos.distance( b2->pos ) <= ( b1->radius + b2->radius ) )
    {
        return 1;
    }
    
    return 0;
}

int bBallMgr::border_col( bBall * b )
{
    if( b->pos.x <= b->radius || b->pos.x >= 640-b->radius )
    {
        return 1;
    }
    
    if( b->pos.y <= b->radius || b->pos.y >= 480-b->radius )
    {
        return 2;
    }
    
    return 0;
}

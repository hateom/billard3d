/***************************************************************************
 *   Copyright (C) 2007 by Tomasz Huczek                                   *
 *   tomasz.huczek@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <iostream>
#include "bballmgr.h"
#include "bassert.h"

bBallMgr::bBallMgr() : ball(NULL), size(0)
{
}


bBallMgr::~bBallMgr()
{
    release();
}

bool bBallMgr::create()
{
    size = 6;
    ball = new bBall[size];
    
    ball[0].pos.x  = 100.0;
    ball[0].pos.y  = 100.0;
    ball[0].radius = 50.0;
    ball[0].vel.x  = 40.0;
    ball[0].vel.y  = -15.0;
    
    ball[1].pos.x  = 325.0;
    ball[1].pos.y  = 100.0;
    ball[1].radius = 50.0;
    ball[1].vel.x  = 0.0;
    ball[1].vel.y  = 14.0;
    
    ball[2].pos.x  = 550.0;
    ball[2].pos.y  = 100.0;
    ball[2].radius = 50.0;
    ball[2].vel.x  = -40.0;
    ball[2].vel.y  = 10.0;
    
    ball[3].pos.x  = 100.0;
    ball[3].pos.y  = 300.0;
    ball[3].radius = 50.0;
    ball[3].vel.x  = 40.0;
    ball[3].vel.y  = -20.0;
    
    ball[4].pos.x  = 325.0;
    ball[4].pos.y  = 300.0;
    ball[4].radius = 50.0;
    ball[4].vel.x  = 13.0;
    ball[4].vel.y  = 20.0;
    
    ball[5].pos.x  = 550.0;
    ball[5].pos.y  = 300.0;
    ball[5].radius = 50.0;
    ball[5].vel.x  = -40.0;
    ball[5].vel.y  = 10.0;
    
    return true;
}

void bBallMgr::release()
{
    delete [] ball;
    ball = NULL;
    size = 0;
}

void bBallMgr::draw( bFpsTimer * fps )
{
    BASSERT( fps != NULL );
    
    int bcol;
    
    for( int i=0; i<size; ++i ) {
        ball[i].process( fps->factor() );
        if( ( bcol = border_col( &ball[i] ) ) != 0 ) {
            ball[i].unprocess( fps->factor() );
            if( bcol == 1 ) { // x-border
                ball[i].vel.x *= -1.0;
            } else { // y-border 
                ball[i].vel.y *= -1.0;
            }
        }
        for( int j=0; j<size; ++j ) {
            if( i == j || ball[i].isf() ) continue;
            if( ball_col( &ball[i], &ball[j] ) ) {
                ball[i].unprocess( fps->factor() );
                //ball[j].unprocess( fps.factor() );
                
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
    
    BASSERT( b1 != NULL && b2 != NULL );
    
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
    BASSERT( b1 != NULL && b2 != NULL );
    
    if( b1->pos.distance( b2->pos ) <= ( b1->radius + b2->radius ) ) {
        return 1;
    }
    
    return 0;
}

int bBallMgr::border_col( bBall * b )
{
    BASSERT( b != NULL );
    
    if( b->pos.x <= b->radius || b->pos.x >= 640-b->radius ) {
        return 1;
    }
    
    if( b->pos.y <= b->radius || b->pos.y >= 480-b->radius ) {
        return 2;
    }
    
    return 0;
}

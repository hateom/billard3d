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

#define WALL_VERT   (0xFFFF-1)
#define WALL_HORIZ  (0xFFFF-2)

#define FACTOR 0.96

#define log std::cout

bBallMgr::bBallMgr() : ball(NULL), band(NULL), ball_size(0), band_size(0)
{
}


bBallMgr::~bBallMgr()
{
    release();
}

bool bBallMgr::create()
{
    ball_size = 4;
    ball = new bBall*[ball_size];
    
    band_size = 5;
    band = new bBand*[band_size];
    
    ball[0] = new bBall(ball_size, band_size,
        bVector(300.0,80.0), 
        bVector(230.0,0.0), 
        bVector(0.0,0.0), 50.0);

    ball[1] = new bBall(ball_size, band_size,
        bVector(200.0,100.0), 
        bVector(200.0,500.0), 
        bVector(0.0,0.0), 50.0);
    
    ball[2] = new bBall(ball_size, band_size,
        bVector(220.0,350.0), 
        bVector(300.0,300.0), 
        bVector(0.0,0.0), 50.0);
    
    ball[3] = new bBall(ball_size, band_size,
        bVector(420.0,320.0), 
        bVector(-300.0,300.0), 
        bVector(0.0,0.0), 50.0);
    
    band[0] = new bBand( bVector(  20,  20 ), bVector( 140, 460 ) );
    band[1] = new bBand( bVector( 500, 460 ), bVector( 620,  40 ) );
    band[2] = new bBand( bVector(  20,  20 ), bVector( 620,  40 ) );
    band[3] = new bBand( bVector( 140, 460 ), bVector( 500, 460 ) );
    band[4] = new bBand( bVector( 200, 240 ), bVector( 400, 230 ) );
    
    return true;
}

void bBallMgr::release()
{
    for( int i=0; i<ball_size; ++i )
    {
        delete ball[i];
    }
    
    delete [] ball;
    ball = NULL;
    ball_size = 0;
    
    for( int i=0; i<band_size; ++i )
    {
        delete band[i];
    }
    
    delete [] band;
    band = NULL;
    band_size = 0;
}

void bBallMgr::draw()
{
    for( int i=0; i<ball_size; ++i ) {
        ball[i]->draw();
    }
    
    for( int i=0; i<band_size; ++i ) {
        band[i]->draw();
    }
}

void bBallMgr::collide( bBall * b1, bBall * b2, bVector * o1, bVector * o2 )
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
    /*
    b1->vel = v1;
    b2->vel = v2;
    */
    
    *o1 = v1;
    *o2 = v2;
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

void bBallMgr::process(bFpsTimer * fps)
{
    BASSERT( fps != NULL );
    
    int bcol;
    
    for( int i=0; i<ball_size; ++i ) {
        ball[i]->process( fps->factor() );
    }
    
    // find and mark balls with collisions
    for( int i=0; i<ball_size; ++i ) {
        if( ( bcol = border_col( ball[i] ) ) != 0 ) {
            if( bcol == 1 ) { // x-border
                ball[i]->set_collision( WALL_HORIZ );
            } else { // y-border 
                ball[i]->set_collision( WALL_VERT );
            }
        }
        for( int k=0; k<band_size; ++k ) {
            if( band[k]->is_within( ball[i]->pos, ball[i]->radius ) ) {
                ball[i]->set_band_collision( k );
            }
        }
        for( int j=0; j<ball_size; ++j ) {
            if( i == j || ball[j]->is_collision(i) ) continue;
            if( ball_col( ball[i], ball[j] ) ) {
                 ball[i]->set_collision( j );
                 ball[j]->set_collision( i );
            }
        }
    }
    
    // move backwards balls with collision(s)
    for( int i=0; i<ball_size; ++i ) {
        if( ball[i]->has_collisions() ) {
            ball[i]->unprocess( fps->factor() );
        }
    }
    
    // calculate new velocity vectors 
    // (but no commit - one change changes next calculation result!)
    commit_reflections();
    
    for( int i=0; i<ball_size; ++i ) {
        ball[i]->clear_collisions();   
        // apply velocity vector changes
        ball[i]->commit_v();
        ball[i]->process( fps->factor() );
        for( int k=0; k<band_size; ++k ) {
            if( band[k]->is_within( ball[i]->pos, ball[i]->radius ) ) {
                ball[i]->unprocess( fps->factor() );
            }
        }
        for( int j=0; j<ball_size; ++j ) {
            if( i == j || ball[j]->is_collision(i) ) continue;
            if( ball_col( ball[i], ball[j] ) ) {
                ball[i]->unprocess( fps->factor() );
            }
        }
    }
}

void bBallMgr::commit_reflections()
{
    bBall * b1, * b2;
    bBand * bd;
    bVector v1(0.0,0.0), v2(0.0,0.0), v;
    
    for( int i=0; i<ball_size; ++i )
    {
        b1 = ball[i];
        if( !b1->has_collisions() ) continue;
        
//         log << ">> ball(" << i << "):" << std::endl;
        
        v.zero();
        
//         log << "\tcollisions [" << b1->get_collisions_num() << "] :" << std::endl;
        
        for( int j=0; j<b1->get_collisions_num(); ++j )
        {
            if( b1->get_collision(j) == WALL_VERT ) {
                v1 = b1->vel;
                v1.y *= -1.0;
//                 log << "\t\t* vertical wall" << std::endl;
            } else if( b1->get_collision(j) == WALL_HORIZ ) {
                v1 = b1->vel;
                v1.x *= -1.0;
//                 log << "\t\t* horizontal wall" << std::endl;
            } else {
                b2 = ball[b1->get_collision(j)];
                collide( b1, b2, &v1, &v2 );
//                 log << "\t\t* ball(" << b1->get_collision(j) << ")" << std::endl;
            }
            v += v1;
        }
        for( int j=0; j<b1->get_band_collisions_num(); ++j )
        {
            bd = band[b1->get_band_collision(j)];
            
            collide_band( b1, bd, &v1 );
//             log << "\t\t* band(" << b1->get_band_collision(j) << ") [ " << b1->vel.x << "," << b1->vel.y << " :: " << v1.x << "," << v1.y << " ]" << std::endl;
            v += v1;
        }
        
        v /= (((double)b1->get_collisions_num()) + ((double)b1->get_band_collisions_num()));
        v *= FACTOR;
        
        b1->set_v( v );// / ((double)b1->get_collisions_num());
//         log << "\tcurr vel (" << b1->vel.x << ", " << b1->vel.y << ") |" << b1->vel.length() << "|" << std::endl;
//         log << "\tnew  vel (" << v.x << ", " << v.y << ") |" << v.length() << "|" << std::endl;
    }
}

void bBallMgr::collide_band(bBall * bl, bBand * bd, bVector * vout)
{
    bVector n(bd->p2-bd->p1), v(bl->vel);
    double scal;
    n.normalize();
    //v.normalize();
    
    scal = DotProduct( v, n );
    
    v *= -1.0;
    
    *vout = v + n*scal*2.0;
}


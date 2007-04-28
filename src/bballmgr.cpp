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
#include "blogger.h"

#define FACTOR 0.96

bBallMgr::bBallMgr() : ball(NULL), band(NULL), ball_size(0), band_size(0)
{
}

bBallMgr::~bBallMgr()
{
    release();
}

bool bBallMgr::create()
{
    ball_size = 2;
    ball = new bBall*[ball_size];
    
    band_size = 5;
    band = new bBand*[band_size];
    
    ball[0] = new bBall(
        bVector(300.0,180.0), 
        bVector(230.0,0.0), 
        bVector(0.0,0.0), 50.0);

    ball[1] = new bBall(
        bVector(200.0,100.0), 
        bVector(200.0,500.0), 
        bVector(0.0,0.0), 50.0);
    /*
    ball[2] = new bBall(
        bVector(220.0,350.0), 
        bVector(300.0,300.0), 
        bVector(0.0,0.0), 50.0);
    
    ball[3] = new bBall(
        bVector(420.0,320.0), 
        bVector(-300.0,300.0), 
        bVector(0.0,0.0), 50.0);
    */
    band[0] = new bBand( bVector(  20,  20 ), bVector( 140, 580 ) );
    band[1] = new bBand( bVector( 500, 460 ), bVector( 780,  40 ) );
    band[2] = new bBand( bVector(  20,  20 ), bVector( 790,  40 ) );
    band[3] = new bBand( bVector( 140, 460 ), bVector( 700, 590 ) );
    band[4] = new bBand( bVector( 200, 340 ), bVector( 250, 330 ) );
    
    luball.create( ball_size );
    luband.create( ball_size, band_size, false );
    
    return true;
}

void bBallMgr::release()
{
    luball.release();
    luband.release();
    
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

void bBallMgr::process(bFpsTimer * fps)
{
    BASSERT( fps != NULL );
    
    for( int i=0; i<ball_size; ++i ) {
        ball[i]->process( fps->factor() );
    }
    
    // find and mark balls with collisions
    for( int i=0; i<ball_size; ++i ) {
        for( int k=0; k<band_size; ++k ) {
            bBand::band_piece bp;
            if( (bp = band[k]->is_within( ball[i]->pos, ball[i]->radius )) != bBand::bNone ) {
                if( bp == bBand::bSide ) {
                    luband.set( i, k, 1);
                } else {
                    luband.set( i, k, bp==bBand::bEdge1?2:3);
                }
            }
        }
        for( int j=0; j<i; ++j ) {
            if( ball[i]->collides( ball[j] ) ) {
                 luball.set( i, j, 1 );
            }
        }
    }
    
    // move backwards balls with collision(s)
    for( int i=0; i<ball_size; ++i ) {
        if( is_any(i) ) {
            ball[i]->unprocess( fps->factor() );
        }
    }
    
   
    // calculate new velocity vectors 
    // (but no commit - one change changes next calculation result!)
    commit_reflections();
    
    luball.clear();
    luband.clear();
    
    for( int i=0; i<ball_size; ++i ) {
        // apply velocity vector changes
        ball[i]->commit_v();
/*        ball[i]->process( fps->factor() );
        for( int k=0; k<band_size; ++k ) {
            if( band[k]->is_within( ball[i]->pos, ball[i]->radius ) != bBand::bNone ) {
                ball[i]->unprocess( fps->factor() );
            }
        }
        for( int j=0; j<i; ++j ) {
            if( ball[i]->collides( ball[j] ) ) {
                ball[i]->unprocess( fps->factor() );
            }
        }*/
    }
}

void bBallMgr::commit_reflections()
{
    bVector v;
    bBall * b1, * b2;
    bBand * bd;
    int bdc;
    int flag;
    
    for( int i=0; i<ball_size; ++i ) {
        b1 = ball[i];
        v.zero();
        flag = 0;
        for( int j=0; j<ball_size; ++j ) {
            b2 = ball[j];
            if( i!=j && luball.at(i,j) != 0 ) {
                BLOG( ">> collision %d with %d\n", i, j );
                std::cout << luball;
                v += b1->collision( b2 );
                flag++;
            }
        }
        for( int j=0; j<band_size; ++j ) {
            bd = band[j];
            if( (bdc = luband.at( i, j )) != 0 ) {
                flag++;
                if( bdc == 1 ) {
                    v += b1->collision( bd );
                } else if( bdc == 2 ) {
                    v += b1->collision( bd, bBand::bEdge1 );
                } else if( bdc == 3 ){
                    v += b1->collision( bd, bBand::bEdge2 );
                }
            }
        }
        if( flag != 0 ) {
            BLOG( ">> ball %d -> setting velocity: %2.2f,%2.2f divided by %d\n", i, v.x, v.y, flag );
            b1->set_v( v/(double)flag );
        }
    }
}

bool bBallMgr::is_any(int ball)
{
    for( int i=0; i<ball_size; ++i ) {
        if( luball.at( ball, i ) != 0 ) return true;
    }
    for( int i=0; i<band_size; ++i ) {
        if( luband.at( ball, i ) != 0 ) return true;
    }
    
    return false;
}


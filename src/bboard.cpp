/***************************************************************************
 *   Copyright (C) 2007 by                                       *
 *                                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include "bboard.h"
#include "bassert.h"
#include "blogger.h"
#include "bsdl.h"
#include "bfontmgr.h"
#include "btrace.h"
#include "bprofiler.h"

#define FACTOR 0.96

bBoard::bBoard() : bSingleton<bBoard>(), 
    ball(NULL), band(NULL), ball_size(0), band_size(0)
{
}

bBoard::~bBoard()
{
    release();
}

bool bBoard::create()
{
    guard(bBoard::create);
    
    double tm = 0.0;
    
    ball_size = 4;
    ball = new bBall*[ball_size];
    
    ball[0] = new bBall(
        bVector(400.0,180.0), 
        bVector(230.0,0.0), 
        bVector(tm,tm), 30.0, 1.0, 1.0f, 0.4f, 0.3f );

    ball[1] = new bBall(
        bVector(300.0,200.0), 
        bVector(200.0,500.0), 
        bVector(tm,tm), 30.0, 1.0, 0.3f, 1.0f, 0.4f );
    
    ball[2] = new bBall(
        bVector(220.0,350.0), 
        bVector(300.0,300.0), 
        bVector(0.0,0.0), 30.0, 1.0, 0.4f, 0.3f, 1.0f );
    
    ball[3] = new bBall(
        bVector(180.0,420.0), 
        bVector(-300.0,300.0), 
        bVector(0.0,0.0), 30.0, 1.0, 1.0f, 0.2f, 0.8f );

    band_size = 12;
    band = new bBand*[band_size];

    band[0]  = new bBand( bVector(  65, 150 ), bVector( 200,  50 ) );
    band[1]  = new bBand( bVector( 200,  50 ), bVector( 400, 100 ) );
    band[2]  = new bBand( bVector( 400, 100 ), bVector( 600,  50 ) );
    band[3]  = new bBand( bVector( 600,  50 ), bVector( 730, 150 ) );
    band[4]  = new bBand( bVector( 730, 150 ), bVector( 665, 300 ) );
    band[5]  = new bBand( bVector( 665, 300 ), bVector( 730, 450 ) );
    band[6]  = new bBand( bVector( 730, 450 ), bVector( 600, 550 ) );
    band[7]  = new bBand( bVector( 600, 550 ), bVector( 400, 500 ) );
    band[8]  = new bBand( bVector( 400, 500 ), bVector( 200, 550 ) );
    band[9]  = new bBand( bVector( 200, 550 ), bVector(  65, 450 ) );
    band[10] = new bBand( bVector(  65, 450 ), bVector( 130, 300 ) );
    band[11] = new bBand( bVector( 130, 300 ), bVector(  65, 150 ) );
    
    luball.create( ball_size );
    luband.create( ball_size, band_size, false );
    
    return true;
    
    unguard;
}

void bBoard::release()
{
    guard(bBoard::release);
    
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
    
    unguard;
}

void bBoard::draw()
{
    Profiler.begin("ball_mgr::draw_balls");
    for( int i=0; i<ball_size; ++i ) {
        ball[i]->draw();
    }
    Profiler.end("ball_mgr::draw_balls");
    
    Profiler.begin("ball_mgr::draw_bands");
    for( int i=0; i<band_size; ++i ) {
        band[i]->draw();
    }
    Profiler.end("ball_mgr::draw_bands");
    
    glEnable( GL_TEXTURE_2D );
    for( int i=0; i<ball_size; ++i ) {
        PRINT( (int)ball[i]->pos.x-1-(int)ball[i]->radius/2, (int)ball[i]->pos.y-9, 
                B_FONT_DARK, "%2.2f", ball[i]->vel.length() );
        PRINT( (int)ball[i]->pos.x-(int)ball[i]->radius/2, (int)ball[i]->pos.y-8, 
                B_FONT_LIGHT, "%2.2f", ball[i]->vel.length() );
    }
    glDisable( GL_TEXTURE_2D );
}

void bBoard::process(bFpsTimer * fps)
{
    guard(bBoard::process);
    
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
    
   
    Profiler.begin( "ball_mgr::reflections" );
    
    // calculate new velocity vectors 
    // (but no commit - one change changes next calculation result!)
    commit_reflections();
    
    Profiler.end( "ball_mgr::reflections" );
    
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
    
    unguard;
}

void bBoard::commit_reflections()
{
    guard(bBoard::commit_reflections);
    
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
            b1->report_collision(flag);
        }
    }
    
    unguard;
}

bool bBoard::is_any(int ball)
{
    guard(bBoard::is_any);
    
    for( int i=0; i<ball_size; ++i ) {
        if( luball.at( ball, i ) != 0 ) return true;
    }
    for( int i=0; i<band_size; ++i ) {
        if( luband.at( ball, i ) != 0 ) return true;
    }
    
    return false;
    
    unguard;
}

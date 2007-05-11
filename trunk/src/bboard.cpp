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
#include "bpath.h"

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
        bVector(4.0,1.8), 
        bVector(2.3,0.0), 
        bVector(tm,tm), 0.3, 1.0, 1.0f, 0.4f, 0.3f );

    ball[1] = new bBall(
        bVector(3.0,2.0), 
        bVector(2.0,5.0), 
        bVector(tm,tm), 0.3, 1.0, 0.3f, 1.0f, 0.4f );
    
    ball[2] = new bBall(
        bVector(2.2,3.5), 
        bVector(3.0,3.0), 
        bVector(0.0,0.0), 0.3, 1.0, 0.4f, 0.3f, 1.0f );
    
    ball[3] = new bBall(
        bVector(1.8,4.2), 
        bVector(-3.0,3.0), 
        bVector(0.0,0.0), 0.3, 1.0, 1.0f, 0.2f, 0.8f );

    band_size = 12;
    band = new bBand*[band_size];

    band[0]  = new bBand( bVector( 0.65, 1.5 ), bVector( 2.0, 0.5 ) );
    band[1]  = new bBand( bVector( 2.00, 0.5 ), bVector( 4.0, 1.0 ) );
    band[2]  = new bBand( bVector( 4.00, 1.0 ), bVector( 6.0, 0.5 ) );
    band[3]  = new bBand( bVector( 6.00, 0.5 ), bVector( 7.3, 1.5 ) );
    band[4]  = new bBand( bVector( 7.30, 1.5 ), bVector( 6.65, 3.0 ) );
    band[5]  = new bBand( bVector( 6.65, 3.0 ), bVector( 7.3, 4.5 ) );
    band[6]  = new bBand( bVector( 7.30, 4.5 ), bVector( 6.0, 5.5 ) );
    band[7]  = new bBand( bVector( 6.00, 5.5 ), bVector( 4.0, 5.0 ) );
    band[8]  = new bBand( bVector( 4.00, 5.0 ), bVector( 2.0, 5.5 ) );
    band[9]  = new bBand( bVector( 2.00, 5.5 ), bVector( 0.65, 4.5 ) );
    band[10] = new bBand( bVector( 0.65, 4.5 ), bVector( 1.30, 3.0 ) );
    band[11] = new bBand( bVector( 1.30, 3.0 ), bVector( 0.65, 1.5 ) );
    
    luball.create( ball_size );
    luband.create( ball_size, band_size, false );
    
	glEnable(GL_TEXTURE_2D);

	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );

	if( !ball_tex.load( GETPATH("../../tex/ball.bmp") ) )
    {
        BLOG( "!! Error loading ball texture!\n" );
    }

    return true;
    
    unguard;
}

void bBoard::release()
{
    guard(bBoard::release);
    
	ball_tex.release();

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
    glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 0.2f, 0.2f, 0.2f );
        glVertex3d( 0.0, 0.0, 0.0 );
        glColor3f( 0.0f, 0.0f, 0.0f );
        glVertex3d( 0.0, 0.0, 6.0 );
        glColor3f( 0.2f, 0.2f, 0.2f );
        glVertex3d( 8.0, 0.0, 0.0 );
        glColor3f( 0.0f, 0.0f, 0.0f );
        glVertex3d( 8.0, 0.0, 6.0 );
    glEnd();
    
    Profiler.begin("ball_mgr::draw_balls");
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	ball_tex.bind();
    for( int i=0; i<ball_size; ++i ) {
        ball[i]->draw();
    }
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
    Profiler.end("ball_mgr::draw_balls");
    
    Profiler.begin("ball_mgr::draw_bands");
    for( int i=0; i<band_size; ++i ) {
        band[i]->draw();
    }
    Profiler.end("ball_mgr::draw_bands");
/*
    glEnable( GL_TEXTURE_2D );
    for( int i=0; i<ball_size; ++i ) {
        PRINT( (int)ball[i]->pos.x-1-(int)ball[i]->radius/2, (int)ball[i]->pos.y-9, 
                B_FONT_DARK, "%2.2f", ball[i]->vel.length() );
        PRINT( (int)ball[i]->pos.x-(int)ball[i]->radius/2, (int)ball[i]->pos.y-8, 
                B_FONT_LIGHT, "%2.2f", ball[i]->vel.length() );
    }
    glDisable( GL_TEXTURE_2D );
*/
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
                //std::cout << luball;
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

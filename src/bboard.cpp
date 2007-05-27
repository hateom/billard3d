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
#include "bsystem.h"
#include "bboarddata.h"

#include <cmath>

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
    
    ball_size = 7;
    ball = new bBall*[ball_size];
    
    ball[0] = new bBall( bVector( 2.0,1.8),  bVector( 2.3, 0.0), bVector(tm,tm), 0.3, 1.0, 1.0f, 0.8f, 0.6f );
    ball[1] = new bBall( bVector( -2.0,2.0),  bVector( 2.0, 5.0), bVector(tm,tm), 0.3, 1.0, 0.6f, 1.0f, 0.8f );
    ball[2] = new bBall( bVector( -2.2, -1.5),  bVector( 3.0, 3.0), bVector(0.0,0.0), 0.3, 1.0, 0.8f, 0.6f, 1.0f );
    ball[3] = new bBall( bVector( 1.8,0.2),  bVector(-3.0, 3.0), bVector(0.0,0.0), 0.3, 1.0, 1.0f, 0.6f, 0.8f );
    
    ball[4] = new bBall( bVector( 1.8,1.2),  bVector(-3.0, 3.0), bVector(0.0,0.0), 0.3, 1.0, 1.0f, 0.6f, 1.0f );
    ball[5] = new bBall( bVector( 2.1,-2.2),  bVector(-3.0, 3.0), bVector(0.0,0.0), 0.3, 1.0, 0.5f, 0.9f, 1.0f );
    
    ball[6] = new bBall( bVector( -2.1, 1.0),  bVector(-3.0, 3.0), bVector(0.0,0.0), 0.3, 1.0, 1.0f, 1.0f, 1.0f );

    band_size = BOARD_SEGMENTS;
    band = new bBand*[band_size];
/*
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
*/
    for( int i=0; i<BOARD_SEGMENTS-1; ++i ) {
        band[i] = new bBand( 
            bVector( board_data[i].x, board_data[i].y ), 
            bVector( board_data[i+1].x, board_data[i+1].y ) 
        );
    }
    band[BOARD_SEGMENTS-1] = new bBand( 
        bVector( board_data[BOARD_SEGMENTS-1].x, board_data[BOARD_SEGMENTS-1].y ), 
        bVector( board_data[0].x, board_data[0].y ) 
    );
    
    luball.create( ball_size );
    luband.create( ball_size, band_size, false );
    
	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
    
	if( !ball_tex.load( GETPATH("../../tex/ball.bmp") ) ) {
        BLOG( "!! Error loading ball texture!\n" );
    }
    
    if( !ball_num.load( GETPATH("../../tex/xball.bmp") ) ) {
        BLOG( "!! Error loading ball texture!\n" );
    }
    
    if( !desk.load( GETPATH("../../tex/desk.bmp") ) ) {
        BLOG( "!! Error loading desk texture!\n" );
    }
    
    if( !band_tex.load( GETPATH("../../tex/band.bmp") ) ) {
        BLOG( "!! Error loading band texture!\n" );
    }
    
    if( bShader::is_supported() ) {
        if( !ball_shader.load_fragment( GETPATH("../../shaders/ball_frag.cg") ) ) {
            BLOG( "!! Error loading ball shader!\n" );   
        }
        if( !ball_shader.load_vertex( GETPATH("../../shaders/ball_vert.cg") ) ) {
            BLOG( "!! Error loading ball shader!\n" );   
        }
        if( !board_shader.load_fragment( GETPATH("../../shaders/board_frag.cg") ) ) {
            BLOG( "!! Error loading board shader!\n" );   
        }
    } else {
        BLOG( "!! Shaders are not supported!\n" );   
    }

	if( !glewIsSupported("GL_ARB_multitexture") )
	{
		BLOG( "!! Multitexturing is not supported!\n" );
	}

    return true;
    
    unguard;
}

void bBoard::reset()
{
    ball[0]->set_v( bVector( 2.3, 0.0) ); ball[0]->commit_v();
    ball[1]->set_v( bVector( 2.0, 5.0) ); ball[0]->commit_v();
    ball[2]->set_v( bVector( 3.0, 3.0) ); ball[0]->commit_v();
    ball[3]->set_v( bVector(-3.0, 3.0) ); ball[0]->commit_v();
    
    ball[4]->set_v( bVector(-3.0, 3.0) ); ball[0]->commit_v();
    ball[5]->set_v( bVector(-3.0, 3.0) ); ball[0]->commit_v();
    
    ball[6]->set_v( bVector(-3.0, 3.0) ); ball[0]->commit_v();
}

void bBoard::release()
{
    guard(bBoard::release);
    
    board_shader.release();
    ball_shader.release();
    
	ball_tex.release();
    ball_num.release();

    band_tex.release();
    desk.release();
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

void bBoard::draw_balls()
{
    for( int i=0; i<ball_size; ++i ) {
        ball[i]->draw_shadow();
    }
    /*
    glEnable( GL_BLEND );
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_ONE,GL_ZERO);
    */
    
    ball_shader.enable( bShader::B_BOTH );
    ball_shader.bind( bShader::B_BOTH );
    
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    ball_num.bind();
    
    glActiveTextureARB(GL_TEXTURE1_ARB);
    glEnable(GL_TEXTURE_2D);
    ball_tex.bind();
    
    glMultiTexCoord3fARB( GL_TEXTURE2_ARB, 3.0f, 2.0, -2.5f );
    
    for( int i=0; i<ball_size; ++i ) {
        ball[i]->draw( &ball_shader );
    }
    
    glActiveTextureARB(GL_TEXTURE0_ARB);
    
    ball_shader.disable( bShader::B_BOTH );
    
    /*
    glDisable( GL_DEPTH_TEST );
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_DST_ALPHA);
    ball_tex.bind();
    
    for( int i=0; i<ball_size; ++i ) {
        ball[i]->draw();
    }
    */
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable( GL_BLEND );
    
    glEnable( GL_DEPTH_TEST );   
}

void bBoard::draw()
{
    board_shader.enable( bShader::B_FRAGMENT );
    board_shader.bind( bShader::B_FRAGMENT );
    
    glActiveTextureARB( GL_TEXTURE0_ARB );
    glEnable(GL_TEXTURE_2D);
    ball_num.bind();
    
    glMultiTexCoord3fARB( GL_TEXTURE1_ARB, 0.0f, 1.0, 0.0f );
    glMultiTexCoord3fARB( GL_TEXTURE2_ARB, 0.0f, 0.1, 0.0f );
    
    float lx = 0, ly = 0.3f, lz = 0;
/*    
    glEnable( GL_TEXTURE_2D );
    desk.bind();
    glBegin( GL_TRIANGLE_STRIP );
        glNormal3f( 0.0f, 1.0f, 0.0f );
        glMultiTexCoord2fARB( GL_TEXTURE0_ARB, 0, 0 ); 
        glMultiTexCoord3fARB( GL_TEXTURE3_ARB, BMINX-lx, 0.0-ly, BMINY-lz ); 
        glVertex3d( BMINX, 0.0, BMINY );
        glMultiTexCoord2fARB( GL_TEXTURE0_ARB, 0, 1 ); 
        glMultiTexCoord3fARB( GL_TEXTURE3_ARB, BMINX-lx, 0.0-ly, BMAXY-lz ); 
        glVertex3d( BMINX, 0.0, BMAXY );
        glMultiTexCoord2fARB( GL_TEXTURE0_ARB, 1, 0 );
        glMultiTexCoord3fARB( GL_TEXTURE3_ARB, BMAXX-lx, 0.0-ly, BMINY-lz );  
        glVertex3d( BMAXX, 0.0, BMINY );
        glMultiTexCoord2fARB( GL_TEXTURE0_ARB, 1, 1 );
        glMultiTexCoord3fARB( GL_TEXTURE3_ARB, BMAXX-lx, 0.0-ly, BMAXY-lz );  
        glVertex3d( BMAXX, 0.0, BMAXY );
    glEnd();
*/    
    
    glEnable( GL_TEXTURE_2D );
    desk.bind();
    glBegin( GL_TRIANGLE_STRIP );
        glNormal3f( 0.0f, 1.0f, 0.0f );
        for( int i=0; i<DESK_SEGMENTS; ++i ) {
            glMultiTexCoord2fARB( GL_TEXTURE0_ARB, desk_data[i].tx, desk_data[i].ty ); 
            glMultiTexCoord3fARB( GL_TEXTURE3_ARB, desk_data[i].x-lx, 0.0-ly, desk_data[i].y-lz ); 
            glVertex3d( desk_data[i].x, 0.0, desk_data[i].y );
        }
    glEnd();
    
    Profiler.begin("ball_mgr::draw_bands");
    
    glActiveTextureARB( GL_TEXTURE0_ARB );
    glEnable(GL_TEXTURE_2D);
    band_tex.bind();
    
    for( int i=0; i<band_size; ++i ) {
        band[i]->draw();
    }
    
    glMultiTexCoord3dARB( GL_TEXTURE1_ARB, 0.0, 1.0, 0.0 ); 
        
    glBegin( GL_TRIANGLE_STRIP );
    for( int i=0; i<BOARD_SEGMENTS; ++i ) {
        glNormal3d( 0.0, 1.0, 0.0 );
        //glMultiTexCoord3fARB( GL_TEXTURE3_ARB, band_data[i].x, 0.4-ly, band_data[i].y );
        glMultiTexCoord2fARB( GL_TEXTURE0_ARB, ((i%2)==0)?0:1, 0 ); 
        glVertex3d( band_data[i].x,  0.4, band_data[i].y );
        //glMultiTexCoord3fARB( GL_TEXTURE3_ARB, board_data[i].x, 0.4-ly, board_data[i].y );
        glMultiTexCoord2fARB( GL_TEXTURE0_ARB, ((i%2)==0)?0:1, 1 ); 
        glVertex3d( board_data[i].x, 0.4, board_data[i].y );
    }
    //glMultiTexCoord3fARB( GL_TEXTURE3_ARB, band_data[0].x, 0.4-ly, band_data[0].y );
    glMultiTexCoord2fARB( GL_TEXTURE0_ARB, 1, 0 ); 
    glVertex3d( band_data[0].x,  0.4, band_data[0].y );
    //glMultiTexCoord3fARB( GL_TEXTURE3_ARB, board_data[0].x, 0.4-ly, board_data[0].y );
    glMultiTexCoord2fARB( GL_TEXTURE0_ARB, 1, 1 ); 
    glVertex3d( board_data[0].x, 0.4, board_data[0].y );
    glEnd();
    
    glColor3f(0.0f,0.0f,0.2f);
    glBegin( GL_TRIANGLE_STRIP );
    for( int i=0; i<BOARD_SEGMENTS; ++i ) {
        glVertex3d( band_data[i].x,  0.0, band_data[i].y );
        glVertex3d( band_data[i].x,  0.4, band_data[i].y );
    }
    glVertex3d( band_data[0].x,  0.0, band_data[0].y );
    glVertex3d( band_data[0].x,  0.4, band_data[0].y );
    glEnd();
    
    board_shader.disable( bShader::B_FRAGMENT );
    
    Profiler.begin("ball_mgr::draw_balls");
    draw_balls();
    Profiler.end("ball_mgr::draw_balls");
    
    Profiler.end("ball_mgr::draw_bands");
/*
    glEnable( GL_TEXTURE_2D );
    glColor3f( 1.0, 1.0, 1.0 );
    bSystem::video_sys.set_matrix_2d();
    for( int i=0; i<ball_size; ++i ) {
        PRINT( 30, 100+16*i, B_FONT_LIGHT, "%2.2f %2.2f", ball[i]->vel.length(), ball[i]->lphi );
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

void bBoard::sort_balls()
{
    bBall * ptr;
    
    for( int i=0; i<ball_size; ++i ) {
        for( int j=0; j<ball_size-1; ++j ) {
            if( GetCamera.get_distance( ball[j]->pos ) < GetCamera.get_distance( ball[j+1]->pos ) ) {
                ptr = ball[j];
                ball[j] = ball[j+1];
                ball[j+1] = ptr;
            }
        }
    }
}

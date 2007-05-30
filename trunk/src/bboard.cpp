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
#include "boards/bboarddata.h"
#include "bconst.h"

#include <cmath>

bool SameSide( bVector p1, bVector p2, bVector a, bVector b )
{
    bVector a1 = p1 - a;
    bVector a2 = p2 - a;
	double cp1 = (b - a).cross(a1);
	double cp2 = (b - a).cross(a2);
	//cp1 = CrossProduct(b-a, p1-a)
	//cp2 = CrossProduct(b-a, p2-a)

	if( cp1*cp2 >= 0 ) return true; else return false;
}

bool PointInTriangle( bVector p, bVector a, bVector b, bVector c )
{
	if( SameSide( p, a, b, c ) && SameSide( p, b, a, c) && SameSide( p, c, a, b ) ) return true; else return false;
}

//---

bBoard::bBoard() : bSingleton<bBoard>(), 
    ball(NULL), band(NULL), ball_size(0), band_size(0), aa(B_PI), 
    view_r(1.0), power(0.0), camera_type(CT_FPS)
{
}

bBoard::~bBoard()
{
    release();
}

bool bBoard::create()
{
    guard(bBoard::create);
    
    ball_size = BALL_COUNT;
    ball = new bBall*[ball_size];
    
    ball[0] = new bBall( bVector( ball_data[0].x, ball_data[0].y ), bVector( 0, 0 ), bVector( 0, 0 ), 0.3, 1.0, 1.0f, 1.0f, 1.0f );
    
    for( int i=1; i<BALL_COUNT; ++i ) {
        ball[i] = new bBall( bVector( ball_data[i].x, ball_data[i].y ), bVector( 0, 0 ), bVector( 0, 0 ), 0.3, 1.0, 
            0.5f+((float)(rand()%10))/20.0f, 0.5f+((float)(rand()%10))/20.0f, 0.5f+((float)(rand()%10))/20.0f );
    }

    band_size = BOARD_SEGMENTS;
    band = new bBand*[band_size];

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
    
    if( !shadow.load( GETPATH("../../tex/shadow.bmp") ) ) {
        BLOG( "!! Error loading shadow texture!\n" );
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

void bBoard::release()
{
    guard(bBoard::release);
    
    board_shader.release();
    ball_shader.release();
    
    shadow.release();
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
    glActiveTextureARB(GL_TEXTURE0_ARB);
    glEnable(GL_TEXTURE_2D);
    shadow.bind();
    for( int i=0; i<ball_size; ++i ) {
        ball[i]->draw_shadow( bVector3(0.0, 8.0, 0.0) );
    }
    
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
		if( i > 0 ) ball[i]->set_visibility( false );
		for(int j=0; j<DESK_SEGMENTS-2; ++j ) {
			if( PointInTriangle( ball[i]->pos, 
					bVector( desk_data[j].x, desk_data[j].y ), 
					bVector( desk_data[j+1].x, desk_data[j+1].y ), 
					bVector( desk_data[j+2].x, desk_data[j+2].y ) ) ) {
				ball[i]->set_visibility( true );
				break;
			}
		}
		ball[i]->draw( &ball_shader );
    }
    
    glActiveTextureARB(GL_TEXTURE0_ARB);
    
    ball_shader.disable( bShader::B_BOTH );
    
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable( GL_BLEND );
    
    glEnable( GL_DEPTH_TEST );   
}

void bBoard::draw()
{
    double vvx = cos(aa), vvy = sin(aa);
    
    if( idle() && camera_type == CT_FPS ) {
        GetCamera.set_eye( bVector3( ball[0]->pos.x - 2*view_r*vvx, 2.0, ball[0]->pos.y - 2*view_r*vvy ) );
        GetCamera.set_dst( bVector3( ball[0]->pos.x + 3*view_r*vvx, 0.2, ball[0]->pos.y + 3*view_r*vvy ) );
    } else {
        GetCamera.set_top_view();   
    }
    
    glDisable( GL_TEXTURE_2D );
    glColor3f( 0.0, 0.0, 0.0 );
    glBegin( GL_TRIANGLE_STRIP );
    for( int i=0; i<BOTTOM_SEGMENTS; ++i ) {
        glVertex3d( bottom_data[i].x, -0.01, bottom_data[i].y );
    }
    glEnd();
    
    if( idle() ) {
        glLineWidth( 2.0 );
        glEnable( GL_LINE_SMOOTH );
        glBegin( GL_LINES );
            glColor4d( 1.0, 0.3, 0.3, 1.0 );
            for(double k=0.0; k<4.0; k+=0.2) {
                glVertex3d( ball[0]->pos.x+vvx*k, ball[0]->radius, ball[0]->pos.y+vvy*k );
            }
        glEnd();
        glDisable( GL_BLEND );
    }
    
    glColor3f( 1.0, 1.0, 1.0 );
    
    board_shader.enable( bShader::B_FRAGMENT );
    board_shader.bind( bShader::B_FRAGMENT );
    
    glActiveTextureARB( GL_TEXTURE0_ARB );
    glEnable(GL_TEXTURE_2D);
    ball_num.bind();
    
    glMultiTexCoord3fARB( GL_TEXTURE1_ARB, 0.0f, 1.0f, 0.0f );
    glMultiTexCoord3fARB( GL_TEXTURE2_ARB, 0.0f, 0.1f, 0.0f );
    
    float lx = 0, ly = 0.3f, lz = 0;
    
    glEnable( GL_TEXTURE_2D );
    desk.bind();
    glBegin( GL_TRIANGLE_STRIP );
        glNormal3f( 0.0f, 1.0f, 0.0f );
        for( int i=0; i<DESK_SEGMENTS; ++i ) {
            glMultiTexCoord2dARB( GL_TEXTURE0_ARB, desk_data[i].tx, desk_data[i].ty ); 
            glMultiTexCoord3dARB( GL_TEXTURE3_ARB, desk_data[i].x-lx, 0.0-ly, desk_data[i].y-lz ); 
            glVertex3d( desk_data[i].x, 0.0, desk_data[i].y );
        }
    glEnd();
    
    Profiler.begin("ball_mgr::draw_bands");
    
    glActiveTextureARB( GL_TEXTURE0_ARB );
    glEnable(GL_TEXTURE_2D);
    band_tex.bind();
    
    glDisable( GL_CULL_FACE );
    for( int i=0; i<band_size; ++i ) {
        band[i]->draw();
    }
    
    glMultiTexCoord3dARB( GL_TEXTURE1_ARB, 0.0, 1.0, 0.0 ); 
        
    glBegin( GL_TRIANGLE_STRIP );
    for( int i=0; i<BOARD_SEGMENTS; ++i ) {
        glNormal3d( 0.0, 1.0, 0.0 );
        //glMultiTexCoord3fARB( GL_TEXTURE3_ARB, band_data[i].x, 0.4-ly, band_data[i].y );
        glMultiTexCoord2dARB( GL_TEXTURE0_ARB, ((i%2)==0)?0.0:1.0, 0.0 ); 
        glVertex3d( band_data[i].x,  0.4, band_data[i].y );
        //glMultiTexCoord3fARB( GL_TEXTURE3_ARB, board_data[i].x, 0.4-ly, board_data[i].y );
        glMultiTexCoord2dARB( GL_TEXTURE0_ARB, ((i%2)==0)?0.0:1.0, 1.0 ); 
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
    
    if( power > 0.0 ) {
        bSystem::video_sys.set_matrix_2d();
        glDisable( GL_TEXTURE_2D );
        glDisable( GL_DEPTH_TEST );
        glColor3f( 0.0f, 0.0f, 0.0f );
        glBegin( GL_TRIANGLE_STRIP );
            glVertex2i( 100, 500 );        
            glVertex2i( 100, 560 );
            glVertex2i( 700, 500 );
            glVertex2i( 700, 560 );
        glEnd();
        
        glBegin( GL_TRIANGLE_STRIP );
            glColor3f( 0.0f, 1.0f, 0.0f );
            glVertex2i( 102, 502 );
            glVertex2i( 102, 558 );
            glColor3d( power/18.2, 1.0-power/18.2, 0.0f );
            glVertex2d( 100.0 + (598.0*power)/18.2, 502 );
            glVertex2d( 100.0 + (598.0*power)/18.2, 558 );
        glEnd();
    }
    
    Profiler.end("ball_mgr::draw_bands");
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

void bBoard::shoot()
{
    if( !idle() ) return;
    
    ball[0]->vel.x = power*cos(aa);
    ball[0]->vel.y = power*sin(aa);
}

bool bBoard::idle()
{
    for( int i=0; i<ball_size; ++i ) {
        if( ball[i]->vel.length() > 0.0 ) return false;
    }
    
    return true;
}

void bBoard::switch_camera()
{
    if( camera_type == CT_FPS ) {
        camera_type = CT_TOP; 
    } else  {
        camera_type = CT_FPS; 
    }
}

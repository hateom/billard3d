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
 
#include "bball.h"
#include "bvideo.h"
#include "bsdl.h"
#include "btrace.h"
#include "bprofiler.h"
#include "blightmgr.h"

//---------------------------------------------------------------------------------------------

bVideo::bVideo() : info(0), width(0), height(0), bpp(0), flags(0), status(false)
{
}

//---------------------------------------------------------------------------------------------

bVideo::~bVideo()
{
    release();
}

//---------------------------------------------------------------------------------------------

bool bVideo::setup(uint32 scr_w, uint32 scr_h, uint32 depth, bool fs)
{
    guard(bVideo::setup);
    
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ) {
        release();
        BASSERTM( 0, "Video initialization failed: " << SDL_GetError() );
        return false;
    }

    info = SDL_GetVideoInfo( );

    if( !info ) {
        release();
        BASSERTM( 0, "Video query failed: " << SDL_GetError() );
        return false;
    }

    width = scr_w;
    height = scr_h;
    bpp = info->vfmt->BitsPerPixel;

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE,        5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,      5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,       5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,     16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,    1 );

    flags = SDL_OPENGL;
    if( fs ) flags |= SDL_FULLSCREEN;

    if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 ) {
        release();
        BASSERTM( 0, "Video mode set failed: " << SDL_GetError() );
        return false;
    }

    glShadeModel( GL_SMOOTH );

    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );

    glDisable( GL_TEXTURE_2D );
    glClearColor( 0, 0, 0, 0 );
    
    glEnable( GL_DEPTH_TEST );
    
    bLightMgr::set_defaults();
    
    status = true;
    return true;
    
    unguard;
}

//---------------------------------------------------------------------------------------------

void bVideo::buffers()
{
    SDL_GL_SwapBuffers();
}

//---------------------------------------------------------------------------------------------

void bVideo::release()
{
    guard(bVideo::release);
    
    if( status ) {
        SDL_Quit();
        status = false;
    }
    
    unguard;
}

//---------------------------------------------------------------------------------------------

void bVideo::set_matrix_2d( uint32 w, uint32 h )
{
    guard(bVideo::set_matrix_2d);

    uint32 mw, mh;
    
    if( w != 0 ) mw = w; else mw = width;
    if( h != 0 ) mh = h; else mh = height;

    glViewport( 0, 0, mw, mh );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho( 0, mw, mh, 0, -100, 100 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    unguard;
}

void bVideo::set_matrix_3d( uint32 w, uint32 h )
{
    guard(bVideo::set_matrix_3d);

    uint32 mw, mh;
    
    if( w != 0 ) mw = w; else mw = width;
    if( h != 0 ) mh = h; else mh = height;

    glViewport( 0, 0, mw, mh );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    gluPerspective( 45.0f, (GLfloat)((GLfloat)mw / (GLfloat)mh), 1.0f, 200.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    unguard;
}

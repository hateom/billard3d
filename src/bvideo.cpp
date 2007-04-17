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

bool bVideo::setup()
{
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 ) {
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError() );
        release();
    }

    info = SDL_GetVideoInfo( );

    if( !info ) {
        fprintf( stderr, "Video query failed: %s\n", SDL_GetError() );
        release();
    }

    width = 640;
    height = 480;
    bpp = info->vfmt->BitsPerPixel;

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE,        5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,      5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,       5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,     16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,    1 );

    flags = SDL_OPENGL; // | SDL_FULLSCREEN;

    if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 ) {
        fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError() );
        release();
    }

    glShadeModel( GL_SMOOTH );

    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );
    //glDisable( GL_CULL_FACE );

    glDisable( GL_TEXTURE_2D );
    glClearColor( 0, 0, 0, 0 );
    
    resize( width, height );
    status = true;
    return true;
}

//---------------------------------------------------------------------------------------------

void bVideo::buffers()
{
//    SDL_Delay(10);
    SDL_GL_SwapBuffers();
}

//---------------------------------------------------------------------------------------------

void bVideo::handle_key( SDL_keysym* keysym )
{
    switch( keysym->sym ) {
        case SDLK_ESCAPE:
            status = false;
            break;
        case SDLK_SPACE:
            break;
        default:
            break;
    }   
}

//---------------------------------------------------------------------------------------------

bool bVideo::messages()
{
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {

        switch( event.type ) {
            case SDL_KEYDOWN:
                handle_key( &event.key.keysym );
                break;
            case SDL_QUIT:
                status = false;
                break;
        }

    }
    
    return status;
}

//---------------------------------------------------------------------------------------------

void bVideo::resize( int width, int height )
{
    glViewport( 0, 0, width, height );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho( 0, width, height, 0, -100, 100 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();  
}

//---------------------------------------------------------------------------------------------

void bVideo::release()
{
    SDL_Quit();
    status = false;
}

//---------------------------------------------------------------------------------------------

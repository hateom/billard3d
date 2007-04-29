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

#include "bdraw.h"
#include "bball.h"
#include "bsdl.h"
#include "bfontmgr.h"

bDraw::bDraw()
{
}

bDraw::~bDraw()
{
}

void bDraw::draw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    bmgr.process( &fps );
    bmgr.draw();
    
	glEnable( GL_TEXTURE_2D );
	PRINT( 10, 10, DG_FONT_LIGHT, "Hello World!" );
	glDisable( GL_TEXTURE_2D );

    /*
    glColor3f( 1.0f, 1.0f, 1.0f );
    bOutputMgr::get_singleton().print( 2.2, 2.2, "Boom!" );
    */
    
    fps.calc();
}
/*
Uint32 sec_call( Uint32 intervall, void * parameter )
{
    static char title[64] = "";
    bFpsTimer * fps = (bFpsTimer*)parameter;
    sprintf( title, "Billard 3D, %d fps, %f", fps->fps(), fps->factor() );
    SDL_WM_SetCaption( title, 0 );
    
    return intervall;
}
*/
bool bDraw::create()
{
    if( !bmgr.create() ) return false;
    
    //sec_timer = SDL_AddTimer( 1000, sec_call, (void*)&fps );
    
    return true;
}

void bDraw::release()
{
    //SDL_RemoveTimer( sec_timer );
    bmgr.release();    
}
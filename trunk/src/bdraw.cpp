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
    PRINT( 10, 10, DG_FONT_LIGHT, ":: billard 3D DEBUG edition", fps.fps() );
	PRINT( 10, 30, DG_FONT_LIGHT, ":: %d fps", fps.fps() );
	glDisable( GL_TEXTURE_2D );

    fps.calc();
}

bool bDraw::create()
{
    if( !bmgr.create() ) return false;
   
    return true;
}

void bDraw::release()
{
    bmgr.release();    
}

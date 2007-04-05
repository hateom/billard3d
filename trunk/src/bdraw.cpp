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

#include <GL/gl.h>
#include <GL/glu.h>
#include "bdraw.h"
#include "bball.h"

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

    bmgr.draw();
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

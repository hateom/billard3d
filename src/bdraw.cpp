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
#include "btrace.h"
#include "bprofiler.h"
#include "bboard.h"

bDraw::bDraw()
{
}

bDraw::~bDraw()
{
}

void bDraw::draw()
{
    glClearColor( 0.0f, 0.2f, 0.23f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

bool bDraw::create()
{
    guard(bDraw::create);
    
    return true;
    
    unguard;
}

void bDraw::release()
{
    guard(bDraw::release);
    unguard;
}

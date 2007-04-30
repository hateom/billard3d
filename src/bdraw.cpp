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

bDraw::bDraw()
{
}

bDraw::~bDraw()
{
}

void bDraw::draw()
{
	guard(bDraw::draw);

    Profiler.start_frame();
    Profiler.begin("main::frame");
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    Profiler.begin("ball_mgr::process");
        bmgr.process( &fps );
    Profiler.end("ball_mgr::process");
    
    Profiler.begin("ball_mgr::draw");
        bmgr.draw();
    Profiler.end("ball_mgr::draw");
    
    Profiler.begin("draw::stats");
	glEnable( GL_TEXTURE_2D );
    PRINT( 10, 10, B_FONT_LIGHT, ":: billard 3D DEBUG edition || compiled %s at %s", __DATE__, __TIME__ );
	PRINT( 10, 30, B_FONT_LIGHT, ":: %d fps", fps.fps() );
    Profiler.end("draw::stats");
    fps.calc();
    Profiler.end("main::frame");

    if( Profiler.is_opened() ) {
        glDisable( GL_TEXTURE_2D );
        glBegin( GL_TRIANGLE_STRIP );
            glColor4f( 1.0f, 1.0f, 1.0f, 0.5f );
            glVertex2i( 479, 449 );
            glVertex2i( 479, 600 );
            glVertex2i( 800, 449 );
            glVertex2i( 800, 600 );
        glEnd();
        glBegin( GL_TRIANGLE_STRIP );
            glColor4f( 0.0f, 0.0f, 0.0f, 0.5f );
            glVertex2i( 480, 450 );
            glVertex2i( 480, 600 );
            glVertex2i( 800, 450 );
            glVertex2i( 800, 600 );
        glEnd();
        glEnable( GL_TEXTURE_2D );
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
        Profiler.write(500, 460, B_FONT_LIGHT);
    }
    
    glDisable( GL_TEXTURE_2D );

	unguard;
}

bool bDraw::create()
{
    guard(bDraw::create);
    
    if( !bmgr.create() ) return false;
    return true;
    
    unguard;
}

void bDraw::release()
{
    guard(bDraw::release);
    bmgr.release();    
    unguard;
}

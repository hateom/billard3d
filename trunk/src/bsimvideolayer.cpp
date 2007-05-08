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

#include "bsimvideolayer.h"
#include "bprofiler.h"
#include "bboard.h"
#include "bsdl.h"
#include "bfontmgr.h"
#include "bsystem.h"
#include "blightmgr.h"

bSimVideoLayer::bSimVideoLayer()
 : bVideoLayer()
{
    g_board.create();
}


bSimVideoLayer::~bSimVideoLayer()
{
    g_board.release();
}

void bSimVideoLayer::draw()
{
    Profiler.start_frame();
    Profiler.begin("main::frame");
    
    bLightMgr::on();
    
    bSystem::video_sys.set_matrix_3d();
    glEnable( GL_DEPTH_TEST );
    gluLookAt( 4.0, 6.0, 0.0, 
               4.0, 0.0, 3.0, 
               0.0, 1.0, 1.0 );
    
    Profiler.begin("ball_mgr::draw");
        //glDisable( GL_TEXTURE_2D );
		glEnable( GL_TEXTURE_2D );
        GetBoard.draw();
    Profiler.end("ball_mgr::draw");
    
    bLightMgr::off();
    
    glDisable( GL_DEPTH_TEST );
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    bSystem::video_sys.set_matrix_2d();
    Profiler.begin("draw::stats");
        glEnable( GL_TEXTURE_2D );
        PRINT( 10, 10, B_FONT_LIGHT, ":: billard 3D DEBUG edition || compiled %s at %s", __DATE__, __TIME__ );
        PRINT( 10, 30, B_FONT_LIGHT, ":: %d fps", GetFps.fps() );
    Profiler.end("draw::stats");
    Profiler.end("main::frame");

    if( Profiler.is_opened() ) {
        glDisable( GL_TEXTURE_2D );
        glBegin( GL_TRIANGLE_STRIP );
            glColor4f( 1.0f, 0.3f, 0.3f, 1.0f );
            glVertex2i( 479, 389 );
            glColor4f( 0.0f, 0.0f, 0.0f, 1.0f );
            glVertex2i( 479, 600 );
            glVertex2i( 800, 389 );
            glVertex2i( 800, 600 );
        glEnd();
        glBegin( GL_TRIANGLE_STRIP );
            glColor4f( 0.0f, 0.0f, 0.0f, 0.5f );
            glVertex2i( 480, 390 );
            glVertex2i( 480, 600 );
            glVertex2i( 800, 390 );
            glVertex2i( 800, 600 );
        glEnd();
        glEnable( GL_TEXTURE_2D );
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
        Profiler.write(500, 400, B_FONT_LIGHT);
    }
}


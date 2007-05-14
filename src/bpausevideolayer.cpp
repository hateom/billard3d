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

#include "bpausevideolayer.h"
#include "bsdl.h"
#include "bfontmgr.h"
#include "bsystem.h"

bPauseVideoLayer::bPauseVideoLayer()
 : bVideoLayer()
{
}


bPauseVideoLayer::~bPauseVideoLayer()
{
}


void bPauseVideoLayer::draw()
{
    bSystem::video_sys.set_matrix_2d();
    
    glDisable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glBlendFunc( GL_ONE, GL_DST_COLOR );
    
    glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 1.0f, 0.2f, 0.2f );
        glVertex2i( 200, 200 );
        glColor3f( 0.0f, 0.0f, 0.0f );
        glVertex2i( 200, 600 );
        glVertex2i( 800, 200 );
        glVertex2i( 800, 600 );
    glEnd();
    
    glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 0.0f, 0.0f, 0.0f );
        glVertex2i( 201, 201 );
        glVertex2i( 201, 599 );
        glVertex2i( 799, 201 );
        glColor3f( 0.1f, 0.1f, 0.1f );
        glVertex2i( 799, 599 );
    glEnd();
    
    glColor3f( 1.0f, 1.0f, 1.0f );
    
    glEnable( GL_TEXTURE_2D );
    glDisable( GL_BLEND );
    
    PRINTB( 432, 302, B_FONT_DARK, "PAUSE" );
    PRINTB( 430, 300, B_FONT_LIGHT, "PAUSE" );
    
    PRINTB( 352, 362, B_FONT_DARK, "Q - quit" );
    PRINTB( 350, 360, B_FONT_LIGHT, "Q - quit" );
    
    PRINTB( 352, 402, B_FONT_DARK, "ESC - back to the game" );
    PRINTB( 350, 400, B_FONT_LIGHT, "ESC - back to the game" );
}



void bPauseVideoLayer::init()
{
}

void bPauseVideoLayer::release()
{
}

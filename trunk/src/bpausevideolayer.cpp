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

bPauseVideoLayer::bPauseVideoLayer()
 : bVideoLayer()
{
}


bPauseVideoLayer::~bPauseVideoLayer()
{
}


void bPauseVideoLayer::draw()
{
    glDisable( GL_TEXTURE_2D );
    
    glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 1.0f, 1.0f, 1.0f );
        glVertex2i( 100, 100 );
        glVertex2i( 100, 500 );
        glVertex2i( 700, 100 );
        glVertex2i( 700, 500 );
    glEnd();
    
    glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 0.1f, 0.1f, 0.1f );
        glVertex2i( 102, 102 );
        glVertex2i( 102, 498 );
        glVertex2i( 698, 102 );
        glVertex2i( 698, 498 );
    glEnd();
    
    glColor3f( 1.0f, 1.0f, 1.0f );
    
    glEnable( GL_TEXTURE_2D );
    
    PRINT( 250, 200, B_FONT_LIGHT, "PAUSE (press Q to quit)" );
}


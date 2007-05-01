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
    glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 0.2f, 0.2f, 0.2f );
        glVertex2i( 100, 100 );
        glVertex2i( 100, 500 );
        glVertex2i( 700, 100 );
        glVertex2i( 700, 500 );
    glEnd();
    
    PRINT( 250, 200, B_FONT_LIGHT, "PAUSE (press escape to continue)" );
}


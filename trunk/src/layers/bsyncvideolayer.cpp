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

#include "bsyncvideolayer.h"
#include "bfontmgr.h"
#include "bgl.h"
#include "bsystem.h"
#include "bconfigreader.h"

bSyncVideoLayer::bSyncVideoLayer()
 : bVideoLayer()
{
}


bSyncVideoLayer::~bSyncVideoLayer()
{
}

void bSyncVideoLayer::draw()
{
    int w = GetConfig.screen_w, h = GetConfig.screen_h;
    glPushMatrix();
        glColor4d( 0.1, 0.1, 0.2, 1.0 );
        bSystem::video_sys.set_matrix_2d();
        glBegin( GL_TRIANGLE_STRIP );
            glVertex2i( 0, 0 );
            glVertex2i( 0, 600 );
            glVertex2i( 800, 0 );
            glVertex2i( 800, 600 );
        glEnd();
        glColor4d( 1.0, 1.0, 1.0, 1.0 );
        PRINTB( 250, 300, B_FONT_LIGHT, "...SYNCHRONIZING FPS TIMER..." );
    glPopMatrix();
}

void bSyncVideoLayer::init( bLogicLayer * )
{
}

void bSyncVideoLayer::release()
{
}


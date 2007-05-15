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

bSyncVideoLayer::bSyncVideoLayer()
 : bVideoLayer()
{
}


bSyncVideoLayer::~bSyncVideoLayer()
{
}

void bSyncVideoLayer::draw()
{
    glPushMatrix();
        glColor4d( 1.0, 1.0, 1.0, 1.0 );
        PRINTB( 200, 300, B_FONT_LIGHT, "...SYNCHRONIZING FPS TIMER..." );
    glPopMatrix();
}

void bSyncVideoLayer::init()
{
}

void bSyncVideoLayer::release()
{
}


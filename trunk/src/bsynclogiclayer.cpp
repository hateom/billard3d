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

#include "bsynclogiclayer.h"
#include "bstatemachine.h"
#include "bsdl.h"

bSyncLogicLayer::bSyncLogicLayer()
 : bLogicLayer(true)
{
}


bSyncLogicLayer::~bSyncLogicLayer()
{
}

void bSyncLogicLayer::init( bVideoLayer * )
{
    active = true;
    ticks = SDL_GetTicks();
}

void bSyncLogicLayer::release()
{
    active = false;
}

void bSyncLogicLayer::update()
{
    if( ( active && ( SDL_GetTicks() - ticks ) > 2000 ) )
    {
        GetStateMachine.go_to( BS_SIMULATION );
        active = false;
    }
}

void bSyncLogicLayer::on_key_down(uint32 key)
{
}

void bSyncLogicLayer::on_key_up(uint32 key)
{
}

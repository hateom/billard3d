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

#include "bsimlogiclayer.h"
#include "bprofiler.h"
#include "bsdl.h"
#include "binput.h"
#include "bsdlsystem.h"
#include "bstatemachine.h"

bSimLogicLayer::bSimLogicLayer()
 : bLogicLayer(true)
{
}


bSimLogicLayer::~bSimLogicLayer()
{
}

void bSimLogicLayer::update()
{
    Profiler.begin("ball_mgr::process");
    GetBoard.process( &GetFps );
    Profiler.end("ball_mgr::process");
}

void bSimLogicLayer::on_key_down(uint32 key)
{
    switch( key ) {
        case SDLK_p:
            Profiler.on_off( !Profiler.is_opened() );
            break;
        case SDLK_ESCAPE:
            GetStateMachine.go_to( BS_PAUSE );
            break;
    }
}

void bSimLogicLayer::on_key_up(uint32 key)
{
    switch( key ) {
        case SDLK_SPACE:
            GetBoard.reset();
            break;
    }
}

void bSimLogicLayer::init()
{
}

void bSimLogicLayer::release()
{
}

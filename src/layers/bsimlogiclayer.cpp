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
#include "blogger.h"
#include "bconst.h"
#include "bcamera.h"

#define MAX_POWER 18.0

bSimLogicLayer::bSimLogicLayer()
 : bLogicLayer(true), ldown(false), rdown(false), sdown(false), shift(false), aa(B_PI), power(0.0)
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
    
    if( rdown ) {
        aa += 0.02;
        if( aa > B_2PI ) aa -= B_2PI;
    }
    
    if( ldown ) {
        aa -= 0.02;
        if( aa < 0.0 ) aa = B_2PI - aa;
    }
    
    if( sdown ) {
        if( power < MAX_POWER ) power += 0.2;
        if( power > MAX_POWER ) power = MAX_POWER;
        GetBoard.set_power( power );
    }
    
    GetBoard.set_aim_angle( aa );
}

void bSimLogicLayer::on_key_down(uint32 key)
{
    switch( key ) {
        case SDLK_RETURN:
            GetBoard.switch_camera();
            break;
        case SDLK_p:
            Profiler.on_off( !Profiler.is_opened() );
            break;
        case SDLK_ESCAPE:
            GetStateMachine.go_to( BS_PAUSE );
            break;
        case SDLK_SPACE:
            sdown = true;
            break;
        case SDLK_LEFT:
            ldown = true;
            break;
        case SDLK_RIGHT:
            rdown = true;
            break;
    }
}

void bSimLogicLayer::on_key_up(uint32 key)
{
    switch( key ) {
        case SDLK_SPACE:
            GetBoard.shoot();
            //GetCamera.set_top_view();
            GetBoard.set_power( power = 0.0 );
            sdown = false;
            break;
        case SDLK_LEFT:
            ldown = false;
            break;
        case SDLK_RIGHT:
            rdown = false;
            break;
    }
}

void bSimLogicLayer::init( bVideoLayer * )
{
}

void bSimLogicLayer::release()
{
}

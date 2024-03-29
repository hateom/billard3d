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

#include "blayermgr.h"
#include "bmainloop.h"

#include "bsimvideolayer.h"
#include "bpausevideolayer.h"
#include "bsimlogiclayer.h"
#include "bpauselogiclayer.h"
#include "bsynclogiclayer.h"
#include "bsyncvideolayer.h"
#include "boptionslogiclayer.h"
#include "boptionsvideolayer.h"
#include "bconsteditlogiclayer.h"
#include "bconsteditvideolayer.h"

#define B_DEFINE_LAYER( ENM, VIDL, LOGL ) vlayer[ENM] = VIDL; llayer[ENM] = LOGL;

bVideoLayer * bLayerMgr::vlayer[bLayer::COUNT] = { NULL };
bLogicLayer * bLayerMgr::llayer[bLayer::COUNT] = { NULL };

void bLayerMgr::init()
{
    B_DEFINE_LAYER( bLayer::SIMULATION, new bSimVideoLayer(),       new bSimLogicLayer() );
    B_DEFINE_LAYER( bLayer::PAUSE,      new bPauseVideoLayer(),     new bPauseLogicLayer() );
	B_DEFINE_LAYER( bLayer::OPTIONS,    new bOptionsVideoLayer(),   new bOptionsLogicLayer() );
    B_DEFINE_LAYER( bLayer::SYNC,       new bSyncVideoLayer(),      new bSyncLogicLayer() );
    B_DEFINE_LAYER( bLayer::CONSTED,    new bConstEditVideoLayer(), new bConstEditLogicLayer() );
}

void bLayerMgr::insert_layer(bLayer::Id layer_id)
{
    vlayer[layer_id]->init( llayer[layer_id] );
    GetMainLoop.insert_video_layer( vlayer[layer_id] );
    
    llayer[layer_id]->init( vlayer[layer_id] );
    GetMainLoop.insert_logic_layer( llayer[layer_id] );
}

void bLayerMgr::remove_layer(bLayer::Id layer_id)
{
    vlayer[layer_id]->release();
    GetMainLoop.remove_video_layer( vlayer[layer_id] );
    
    llayer[layer_id]->release();
    GetMainLoop.remove_logic_layer( llayer[layer_id] );
}

void bLayerMgr::release()
{
    for( int i=0; i<bLayer::COUNT; ++i ) {
        delete vlayer[i]; vlayer[i] = NULL;
        delete llayer[i]; llayer[i] = NULL;
    }
}

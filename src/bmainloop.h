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

#ifndef BMAINLOOP_H
#define BMAINLOOP_H

#include "blockvector.h"
#include "bvideolayer.h"
#include "blogiclayer.h"
#include "bsingleton.h"
#include "bautoeventlistener.h"

#define GetMainLoop bMainLoop::get_singleton()

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bMainLoop: public bSingleton<bMainLoop>, public bAutoEventListener
{
    DEF_LOCK_VECTOR(bVideoLayerList,bVideoLayer*);
    DEF_LOCK_VECTOR(bLogicLayerList,bLogicLayer*);
public:
    bMainLoop();
    virtual ~bMainLoop();

    void insert_video_layer( bVideoLayer * layer );
    void insert_logic_layer( bLogicLayer * layer );
    
    void remove_video_layer( bVideoLayer * layer );
    void remove_logic_layer( bLogicLayer * layer );
    
    void update();
    
    void release();
    
public:
    virtual void on_key_up( uint32 key );
    virtual void on_key_down( uint32 key );
    
private:
    bVideoLayerList video_layer_list;
    bLogicLayerList logic_layer_list;
};

#endif

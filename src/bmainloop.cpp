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

#include "bmainloop.h"
#include "bsystem.h"
#include "bfpstimer.h"

bMainLoop::bMainLoop() : bSingleton<bMainLoop>(), bAutoEventListener()
{
}

bMainLoop::~bMainLoop()
{
    release();
}

void bMainLoop::release()
{
    disconnect_listener();
}

void bMainLoop::update()
{
    GetFps.calc();
    bSystem::draw_sys.draw();
    
    bLogicLayerList::reverse_iterator lit, 
        lbg=logic_layer_list.rbegin(),
        led=logic_layer_list.rend();
        
    bVideoLayerList::iterator vit, 
        vbg=video_layer_list.begin(),
        ved=video_layer_list.end();
        
	video_layer_list.lock();
    for( vit=vbg; vit!=ved; ++vit ) {
        (*vit)->draw();
    }
	video_layer_list.unlock();
    
	logic_layer_list.lock();
    for( lit=lbg; lit!=led; ++lit ) {
        (*lit)->update();
        if( (*lit)->is_exclusive() ) break;
    }
	logic_layer_list.unlock();
}

void bMainLoop::insert_video_layer(bVideoLayer * layer)
{
	video_layer_list.push_back( layer );
}

void bMainLoop::insert_logic_layer(bLogicLayer * layer)
{
	logic_layer_list.push_back( layer );
}

void bMainLoop::remove_logic_layer(bLogicLayer * layer)
{
    bLogicLayerList::iterator it, 
        bg=logic_layer_list.begin(),
        ed=logic_layer_list.end();
        
    for( it=bg; it!=ed; ++it ) {
        if( (*it) == layer ) {
            logic_layer_list.erase( it );
        }
    }
}

void bMainLoop::remove_video_layer(bVideoLayer * layer)
{
    bVideoLayerList::iterator it, 
        bg=video_layer_list.begin(),
        ed=video_layer_list.end();
        
	video_layer_list.lock();
    for( it=bg; it!=ed; ++it ) {
        if( (*it) == layer ) {
            video_layer_list.erase( it );
        }
    }
	video_layer_list.unlock();
}

void bMainLoop::on_key_up(uint32 key)
{
    bLogicLayerList::reverse_iterator lit, 
        lbg=logic_layer_list.rbegin(),
        led=logic_layer_list.rend();
        
	logic_layer_list.lock();
    for( lit=lbg; lit!=led; ++lit ) {
        (*lit)->on_key_up( key );
        if( (*lit)->is_exclusive() ) break;
    }
	logic_layer_list.unlock();
}

void bMainLoop::on_key_down(uint32 key)
{
    bLogicLayerList::reverse_iterator lit, 
        lbg=logic_layer_list.rbegin(),
        led=logic_layer_list.rend();
       
	logic_layer_list.lock();
    for( lit=lbg; lit!=led; ++lit ) {
        (*lit)->on_key_down( key );
        if( (*lit)->is_exclusive() ) break;
    }
	logic_layer_list.unlock();
}

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

#include "binput.h"
#include "btrace.h"
#include "blogger.h"

bInput::bInput()
 : bSingleton<bInput>()
{
}


bInput::~bInput()
{
    release();
}

bool bInput::register_listener(bEventListener * listener)
{
    BLOG( "-- registering event listener (%d)\n", (long)listener );
	list.push_back( listener );
    return true;
}

void bInput::release()
{
    list.clear();
}

bool bInput::unregister_listener(bEventListener * listener)
{
    BLOG( "-- unregistering event listener (%d)\n", (long)listener );
    
    guard(bInput::unregister_listener);
    
    for( bEventListenerVector::iterator it = list.begin(); it != list.end(); ++it ) {
        if( *it == listener ) {
            list.erase( it );
            return true;
        }
    }
    return false;
    
    unguard;
}

void bInput::call_event_key_down(uint32 key)
{
    guard(bInput::call_event_key_down);
    
    list.lock();
    
    for( bEventListenerVector::iterator it = list.begin(); it != list.end(); ++it ) {
        (*it)->on_key_down( key );
    }
    
    list.unlock();
    
    unguard;
}

void bInput::call_event_key_up(uint32 key)
{
    guard(bInput::call_event_key_up);
    
    BLOG( "-- call_event_key_up %d\n", list.size() );
    
    list.lock();
    
    for( bEventListenerVector::iterator it = list.begin(); it != list.end(); ++it ) {
        BLOG( "-- calling key_up event for (%d)\n", (long)(*it) );
        (*it)->on_key_up( key );
    }
    
    list.unlock();
    
    unguard;
}

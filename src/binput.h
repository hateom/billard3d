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

#ifndef BINPUT_H
#define BINPUT_H

#include "blockvector.h"
#include "bsingleton.h"
#include "bassert.h"
#include "beventlistener.h"

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bInput : public bSingleton<bInput>
{
    DEF_LOCK_VECTOR(bEventListenerVector, bEventListener*);
public:
    bInput();
    virtual ~bInput();

    bool register_listener( bEventListener * listener );
    bool unregister_listener( bEventListener * listener );
    void release();
    
    void call_event_key_down( uint32 key );
    void call_event_key_up( uint32 key );
    
private:
    bEventListenerVector list;
    bool is_locked;
};

#endif

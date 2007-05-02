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

#include "bautoeventlistener.h"
#include "binput.h"

bAutoEventListener::bAutoEventListener()
 : bEventListener(), connected(true)
{
    bInput::get_singleton().register_listener(this);
}


bAutoEventListener::~bAutoEventListener()
{
    disconnect_listener();
}

void bAutoEventListener::disconnect_listener()
{
    if( connected ) {
        bInput::get_singleton().unregister_listener(this);    
    }
}

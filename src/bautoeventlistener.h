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

#ifndef BAUTOEVENTLISTENER_H
#define BAUTOEVENTLISTENER_H

#include "beventlistener.h"

/**
    @brief AutoEventListener class
    This listener automatically connects yourself to the input system
    at the creation time, and disconnects when on destructor call.
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bAutoEventListener : public bEventListener
{
public:
    bAutoEventListener();
    virtual ~bAutoEventListener();
    
    void disconnect_listener();
    
protected:
    bool connected;
};

#endif

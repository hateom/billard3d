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

#ifndef BEVENTLISTENER_H
#define BEVENTLISTENER_H

#include "btypes.h"

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bEventListener
{
public:
    bEventListener();
    virtual ~bEventListener();

    virtual void on_key_down( uint32 key ) = 0;
    virtual void on_key_up( uint32 key ) = 0;
};

#endif

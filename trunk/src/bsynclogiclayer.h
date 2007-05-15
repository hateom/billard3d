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

#ifndef BSYNCLOGICLAYER_H
#define BSYNCLOGICLAYER_H

#include "blogiclayer.h"

/**
	@author Tomasz Huczek & Andrzej Jasiński <thuczek@gmail.com>
*/
class bSyncLogicLayer : public bLogicLayer
{
public:
    bSyncLogicLayer();
    virtual ~bSyncLogicLayer();

    void init();
    void release();
    void update();
    
    void on_key_down( uint32 key );
    void on_key_up( uint32 key );
    
private:
    uint32 ticks;
    bool   active;
};

#endif

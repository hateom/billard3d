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

#ifndef BSIMLOGICLAYER_H
#define BSIMLOGICLAYER_H

#include "blogiclayer.h"

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bSimLogicLayer : public bLogicLayer
{
public:
    bSimLogicLayer();
    virtual ~bSimLogicLayer();

    virtual void update();
    
    virtual void on_key_down( uint32 key );
    virtual void on_key_up( uint32 key );
};

#endif

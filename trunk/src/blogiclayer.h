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

#ifndef BLOGICLAYER_H
#define BLOGICLAYER_H

#include "beventlistener.h"

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bLogicLayer: public bEventListener
{
public:
    bLogicLayer( bool exclusiv );
    virtual ~bLogicLayer();

    virtual void update() = 0;
    
    /**
     * @return true if layer is in exclusive mode - bottom layers
     *         won't receive input messages
     */
    bool is_exclusive() const;
    
private:
    bool exclusive;
};

#endif

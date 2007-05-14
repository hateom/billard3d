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

#ifndef BLAYERMGR_H
#define BLAYERMGR_H

#include "bvideolayer.h"
#include "blogiclayer.h"

/**
	@author Tomasz Huczek & Andrzej Jasiński <thuczek@gmail.com>
*/

namespace bLayer {

    enum Id {
        SIMULATION  = 0,
        PAUSE       = 1,
        COUNT       = 2
    };

}

class bLayerMgr
{
public:
    static void insert_layer( bLayer::Id layer_id );
    static void remove_layer( bLayer::Id layer_id );
    
    static void init();
    static void release();
    
private:
    static bVideoLayer * vlayer[bLayer::COUNT];
    static bLogicLayer * llayer[bLayer::COUNT];
};

#endif

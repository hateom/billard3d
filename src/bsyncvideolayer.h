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

#ifndef BSYNCVIDEOLAYER_H
#define BSYNCVIDEOLAYER_H

#include "bvideolayer.h"

/**
	@author Tomasz Huczek & Andrzej Jasiński <thuczek@gmail.com>
*/
class bSyncVideoLayer : public bVideoLayer
{
public:
    bSyncVideoLayer();
    virtual ~bSyncVideoLayer();

    void draw();
    
    void init();
    void release();
};

#endif

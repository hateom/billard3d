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

#ifndef BCONSTEDITVIDEOLAYER_H
#define BCONSTEDITVIDEOLAYER_H

#include "bvideolayer.h"
#include "bconsteditlogiclayer.h"

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bConstEditVideoLayer : public bVideoLayer
{
public:
    bConstEditVideoLayer();
    virtual ~bConstEditVideoLayer();

	void draw();

    void init( bLogicLayer * );
    void release();

private:
	bConstEditLogicLayer * my_logic_layer;
};

#endif

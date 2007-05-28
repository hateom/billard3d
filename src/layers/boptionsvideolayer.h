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

#ifndef BOPTIONSVIDEOLAYER_H
#define BOPTIONSVIDEOLAYER_H

#include "bvideolayer.h"
#include "boptionslogiclayer.h"

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bOptionsVideoLayer : public bVideoLayer
{
public:
    bOptionsVideoLayer();
    virtual ~bOptionsVideoLayer();

	void draw();

    void init( bLogicLayer * );
    void release();

private:
	bOptionsLogicLayer * my_logic_layer;
};

#endif

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

#ifndef BPAUSEVIDEOLAYER_H
#define BPAUSEVIDEOLAYER_H

#include "bvideolayer.h"
#include "bpauselogiclayer.h"

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bPauseVideoLayer : public bVideoLayer
{
public:
    bPauseVideoLayer();
    virtual ~bPauseVideoLayer();

	void draw();

    void init( bLogicLayer * );
    void release();

private:
	bPauseLogicLayer * my_logic_layer;
};

#endif

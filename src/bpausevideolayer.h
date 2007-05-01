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

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bPauseVideoLayer : public bVideoLayer
{
public:
    bPauseVideoLayer();
    virtual ~bPauseVideoLayer();

    virtual void draw();

};

#endif

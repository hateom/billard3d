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

#ifndef BSIMVIDEOLAYER_H
#define BSIMVIDEOLAYER_H

#include "bvideolayer.h"
#include "bboard.h"

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bSimVideoLayer : public bVideoLayer
{
public:
    bSimVideoLayer();
    virtual ~bSimVideoLayer();

    void draw();
    
    void init( bLogicLayer * );
    void release();
    
private:
    bBoard g_board;
    double eyex, eyey, eyez, a;
};

#endif

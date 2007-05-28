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

#ifndef BVIDEOLAYER_H
#define BVIDEOLAYER_H

class bLogicLayer;

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bVideoLayer {
public:
    bVideoLayer();
    virtual ~bVideoLayer();

    virtual void init( bLogicLayer * ) = 0;
    virtual void draw() = 0;
    virtual void release() = 0;
};

#endif

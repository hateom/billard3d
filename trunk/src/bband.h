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

#ifndef BBAND_H
#define BBAND_H

#include "bvector.h"

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bBand {
public:
    bBand();
    bBand( bVector p1, bVector p2 );
    ~bBand();

    void draw();
    double distance( bVector pt );
    
public:
    bVector p1, p2;
};

#endif

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

#ifndef BCAMERA_H
#define BCAMERA_H

#include "bsingleton.h"
#include "bvector3.h"

#define GetCamera bCamera::get_singleton()

/**
	@author Tomasz Huczek & Andrzej Jasiński <thuczek@gmail.com>
*/
class bCamera : public bSingleton<bCamera>
{
public:
    bCamera();
    virtual ~bCamera();
    
    void look_at();
    void update();
    
    bVector3 get_eye() const { return eye; }
    bVector3 get_dest() const { return dest; }
    double get_distance( bVector3 vec );
    
protected:
    bVector3 eye, dest;
    double angle;
};

#endif

/***************************************************************************
 *   Copyright (C) 2007 by Tomasz Huczek                                      *
 *   tomasz.huczek@gmail.com                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef BBALL_H
#define BBALL_H

#include "bvector.h"

/**
	@author Tomasz Huczek <tomasz.huczek@gmail.com>
*/
class bBall{
public:
    bBall();
    ~bBall();
    
    void draw();
    void process( double fps_factor );
    void unprocess( double fps_factor );
    
    void setf( bool ff ) { f = ff; }
    bool isf() { return f; }

public:
    bVector pos, vel, acc;
    double radius;
    double mass;
    
    float r,g,b;
    
    bool f;
};

#endif

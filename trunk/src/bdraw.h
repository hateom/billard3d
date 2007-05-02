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

#ifndef BDRAW_H
#define BDRAW_H

//---------------------------------------------------------------------------------------------

#include "bballmgr.h"
#include "bfpstimer.h"

/**
    @brief Drawing system
	@author Tomasz Huczek <tomasz.huczek@gmail.com>
*/
class bDraw
{
public:
    bDraw();
    ~bDraw();

    bool create();
    void draw();
    void release();
};

//---------------------------------------------------------------------------------------------

#endif

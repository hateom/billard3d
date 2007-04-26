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

#ifndef BBALLMGR_H
#define BBALLMGR_H

//---------------------------------------------------------------------------------------------

#include "bball.h"
#include "bband.h"
#include "bfpstimer.h"
#include "blutable.h"

//---------------------------------------------------------------------------------------------

/**
	@author Tomasz Huczek <tomasz.huczek@gmail.com>
*/
class bBallMgr{
public:
    bBallMgr();
    ~bBallMgr();
    
    bool create();
    void release();
    void process( bFpsTimer * fps );
    void draw();
    bool is_any( int ball );
   
private:
    void commit_reflections();
    bBall ** ball;
    bBand ** band;
    int ball_size;
    int band_size;
    
    bLUTable luball;
    bLUTable luband;
};

//---------------------------------------------------------------------------------------------

#endif

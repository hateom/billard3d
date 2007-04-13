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

#include "bball.h"
#include "bband.h"
#include "bfpstimer.h"

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
    
    // 0 - no collision, 1 - x border, 2 - y border
    int border_col( bBall * b );
    int ball_col( bBall * b1, bBall * b2 );
    void collide( bBall * b1, bBall * b2, bVector * out1, bVector * out2 );
    void collide_band( bBall * bl, bBand * bd, bVector * vout );

   
private:
    void commit_reflections();
    bBall ** ball;
    bBand ** band;
    int ball_size;
    int band_size;
};

#endif

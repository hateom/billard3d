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

#ifndef BBOARD_H
#define BBOARD_H

#include "bsingleton.h"
#include "bball.h"
#include "bband.h"
#include "blutable.h"
#include "bfpstimer.h"

#define GetBoard bBoard::get_singleton()

/**
    @brief Board class
    Defines a board class and usefull methods
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bBoard : public bSingleton<bBoard>
{
public:
    bBoard();
    virtual ~bBoard();

    /// creates board
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

#endif

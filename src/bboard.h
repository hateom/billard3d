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
#include "btexture.h"
#include "bshader.h"

#define GetBoard bBoard::get_singleton()

/**
    @brief Board class
    Defines a board class and usefull methods
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
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
   
    void reset();
    
private:
    void draw_balls();
    void sort_balls();            
    void commit_reflections();
    
private:
    bBall ** ball;
    bBand ** band;
    int ball_size;
    int band_size;
    
    bLUTable luball;
    bLUTable luband;
    
    bShader ball_shader;

	bTexture ball_tex;
    bTexture ball_num;
    bTexture desk;
	GLubyte face[6][64][64][3];
};

#endif


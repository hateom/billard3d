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

#define CT_FPS 0
#define CT_TOP 1

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
   
    void shoot();
    void set_power( double p ) { power = p; }
    bool idle();
    
    void set_aim_angle( double iaa ) { aa = iaa; }
    
    void set_camera_type( int ct ) { camera_type = ct; }
    int  get_camera_type() const { return camera_type; }
    void switch_camera();
    
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
    bShader board_shader;

	bTexture ball_tex;
    bTexture ball_num;
    bTexture band_tex;
    bTexture desk;
    bTexture shadow;
	GLubyte face[6][64][64][3];
    
    double aa, view_r, power;
    int camera_type;
};

#endif


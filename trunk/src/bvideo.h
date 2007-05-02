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
 
#ifndef BVIDEO_H
#define BVIDEO_H

#include "btypes.h"
#include "bfpstimer.h"

struct SDL_VideoInfo;
struct SDL_keysym;

/**
    @brief Video System
	@author Tomasz Huczek <tomasz.huczek@gmail.com>
*/
class bVideo
{
public:
    bVideo();
    ~bVideo();

    bool setup( uint32 scr_w, uint32 scr_h, uint32 depth, bool fs );
    void resize( int width, int height );
    void release();
    void buffers();
    
    void set_matrix_2d( uint32 w=0, uint32 h=0 );
    void set_matrix_3d( uint32 w=0, uint32 h=0 );
   
private:
    bFpsTimer g_fps_timer;
    
    const SDL_VideoInfo *   info;
    int   width;
    int   height;
    int   bpp;
    int   flags;
    bool  status;
};

#endif

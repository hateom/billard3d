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

//---------------------------------------------------------------------------------------------

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

//---------------------------------------------------------------------------------------------

#define SCR_W 800
#define SCR_H 600

//---------------------------------------------------------------------------------------------

/**
	@author Tomasz Huczek <tomasz.huczek@gmail.com>
*/
class bVideo{
public:
    bVideo();
    ~bVideo();

    bool setup();
    void resize( int width, int height );
    void release();
    bool messages();
    void buffers();
    
private:
    void handle_key( SDL_keysym* keysym );
    
private:
    const SDL_VideoInfo *   info;
    int   width;
    int   height;
    int   bpp;
    int   flags;
    bool   status;
};

//---------------------------------------------------------------------------------------------

#endif

//---------------------------------------------------------------------------------------------

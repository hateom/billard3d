/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef BFPSTIMER_H
#define BFPSTIMER_H

#include <sys/time.h>
#include <SDL/SDL.h>

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bFpsTimer{
public:
    bFpsTimer();
    ~bFpsTimer();

    Uint32 calc();
    Uint32 fps() { return frames; }
    
    inline double factor() { 
        return !frames?0.0:1.0/((double)frames); 
    }

/*
    inline double factor() {
        return (t2.tv_usec - t1.tv_usec)*0.0001;
    }
*/    
private:
    timeval t1, t2;
    Uint32 ms;
    Uint32 frames;
    Uint32 curr_frames;
};

#endif

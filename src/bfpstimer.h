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
        if( frames == 0 ) return 0.0; 
        else return 1.0/((double)frames); 
    }
    
private:
    Uint32 ms;
    Uint32 frames;
    Uint32 curr_frames;
};

#endif

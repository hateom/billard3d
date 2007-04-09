/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include "bfpstimer.h"

bFpsTimer::bFpsTimer() 
    : ms(0), frames(0), curr_frames(0)
{
    memset( &t1, 0, sizeof(timeval) );
    memset( &t2, 0, sizeof(timeval) );
}

bFpsTimer::~bFpsTimer()
{
}

Uint32 bFpsTimer::calc()
{
    Uint32 temp;
    temp = SDL_GetTicks();
    
    t1 = t2;
    gettimeofday( &t2, NULL );
    
    if( temp - ms >= 1000 ) {
        ms = temp;
        frames = curr_frames;
        curr_frames = 0;
    }
    
    curr_frames++;
    return curr_frames;
}

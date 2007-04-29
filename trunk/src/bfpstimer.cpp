/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#include "bfpstimer.h"
#include "bsdl.h"

bFpsTimer::bFpsTimer() 
    : ms(0), frames(0), curr_frames(0)
{
}

bFpsTimer::~bFpsTimer()
{
}

Uint32 bFpsTimer::calc()
{
    Uint32 temp;
    temp = SDL_GetTicks();
    
    if( temp - ms >= 1000 ) {
        ms = temp;
        frames = curr_frames;
        curr_frames = 0;
    }
    
    curr_frames++;
    return curr_frames;
}

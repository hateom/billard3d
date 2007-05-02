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

#include "bsingleton.h"

#define GetFps bFpsTimer::get_singleton()

/**
    @brief FPS class
    Class calculates @b FramesPerSeconds
    @warning @b clalc() must be called in every frame
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bFpsTimer: public bSingleton<bFpsTimer> 
{
public:
    bFpsTimer();
    ~bFpsTimer();

    /// recalculates fps
    unsigned int calc();
    
    /// @returns fps
    inline unsigned int fps() const { return frames; }
    
    /// @returns 1.0/fps
    inline double factor() const { 
        return !frames?0.0:1.0/((double)frames); 
        //return 0.006;
    }

private:
    unsigned int ms;
    unsigned int frames;
    unsigned int curr_frames;
};

#endif

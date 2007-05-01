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

//---------------------------------------------------------------------------------------------

#include "bsingleton.h"

//---------------------------------------------------------------------------------------------

#define GetFps bFpsTimer::get_singleton()

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bFpsTimer: public bSingleton<bFpsTimer> {
public:
    bFpsTimer();
    ~bFpsTimer();

    unsigned int calc();
    unsigned int fps() { return frames; }
    
    inline double factor() { 
        return !frames?0.0:1.0/((double)frames); 
        //return 0.006;
    }

/*
    inline double factor() {
        return (t2.tv_usec - t1.tv_usec)*0.0001;
    }
*/    
private:
    unsigned int ms;
    unsigned int frames;
    unsigned int curr_frames;
};

//---------------------------------------------------------------------------------------------

#endif

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

#ifndef BSTATEMACHINE_H
#define BSTATEMACHINE_H

#include "bsingleton.h"

#include "bsimvideolayer.h"
#include "bsimlogiclayer.h"
#include "bpausevideolayer.h"
#include "bpauselogiclayer.h"

#define GetStateMachine bStateMachine::get_singleton()

// 
//  +---------------+           +----------+
//  | BS_SIMULATION | <-------> | BS_PAUSE | -----> QUIT
//  +---------------+           +----------+
// 

typedef enum bState {
    BS_NONE,
    BS_SIMULATION,
    BS_PAUSE,
    BS_SYNC,
    BS_QUIT
};

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bStateMachine : public bSingleton<bStateMachine>
{
public:
    bStateMachine();
    virtual ~bStateMachine();
    
    void go_to( bState new_state );
    
public:
    inline bState get_current_state() const { return state; }
    
private:
    bState state;
    /*
    bSimLogicLayer * sim_logic;
    bSimVideoLayer * sim_video;
    
    bPauseLogicLayer * pause_logic;
    bPauseVideoLayer * pause_video;
    */
};

#endif

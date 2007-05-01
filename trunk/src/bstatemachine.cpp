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

#include "bstatemachine.h"
#include "bsystem.h"

bStateMachine::bStateMachine()
 : bSingleton<bStateMachine>(), state(BS_NONE),
    sim_logic(0), sim_video(0), pause_logic(0), pause_video(0)
{
}


bStateMachine::~bStateMachine()
{
}

void bStateMachine::go_to(bState new_state)
{
    guard(bStateMachine::go_to);
    
    switch(new_state)
    {
        case BS_SIMULATION:
            if( state == BS_NONE ) {
                sim_logic = new bSimLogicLayer();
                sim_video = new bSimVideoLayer();
                GetMainLoop.insert_logic_layer( sim_logic );
                GetMainLoop.insert_video_layer( sim_video );
            } else if( state == BS_PAUSE ) {
                GetMainLoop.remove_logic_layer( pause_logic );
                GetMainLoop.remove_video_layer( pause_video );
                delete pause_logic; pause_logic = 0;
                delete pause_video; pause_video = 0;
            }
            break;
        case BS_PAUSE:
            pause_logic = new bPauseLogicLayer();
            pause_video = new bPauseVideoLayer();
            GetMainLoop.insert_logic_layer( pause_logic );
            GetMainLoop.insert_video_layer( pause_video );
            break;
        case BS_QUIT:
            if( state == BS_PAUSE ) {
                GetMainLoop.remove_logic_layer( pause_logic );
                GetMainLoop.remove_video_layer( pause_video );
                GetMainLoop.remove_logic_layer( sim_logic );
                GetMainLoop.remove_video_layer( sim_video );
                delete pause_logic; pause_logic = 0;
                delete pause_video; pause_video = 0;
                delete sim_logic; sim_logic = 0;
                delete sim_video; sim_video = 0;
            }
            bSDLSystem::quit();
            break;
        case BS_NONE:
            BASSERTM( 0, "Cannot go to this state!" );
            break;
    }
    
    state = new_state;
    
    unguard;
}

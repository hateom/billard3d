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
#include "blayermgr.h"

bStateMachine::bStateMachine()
 : bSingleton<bStateMachine>(), state(BS_NONE)
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
            BLOG( "## changing state to BS_SIMULATION\n" );
            if( state == BS_NONE ) {
                bLayerMgr::insert_layer( bLayer::SIMULATION );
            } else if( state == BS_PAUSE ) {
                bLayerMgr::remove_layer( bLayer::PAUSE );
            }
            break;
        case BS_PAUSE:
            BLOG( "## changing state to BS_PAUSE\n" );
            bLayerMgr::insert_layer( bLayer::PAUSE );
            break;
        case BS_QUIT:
            BLOG( "## changing state to BS_QUIT\n" );
            if( state == BS_PAUSE ) {
                bLayerMgr::remove_layer( bLayer::PAUSE );
                bLayerMgr::remove_layer( bLayer::SIMULATION );
            }
            bSDLSystem::quit();
            break;
        case BS_NONE:
            BLOG( "## changing state to BS_NONE\n" );
            BASSERTM( 0, "Cannot go to this state!" );
            break;
    }
    
    state = new_state;
   
    unguard;
}

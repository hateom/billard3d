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

#include "bsdl.h"
#include "bsdlsystem.h"
#include "binput.h"

bool bSDLSystem::is_running = true;

bSDLSystem::bSDLSystem()
{
}


bSDLSystem::~bSDLSystem()
{
}

bool bSDLSystem::update()
{
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {

        switch( event.type ) {
            case SDL_KEYDOWN:
                bInput::get_singleton().call_event_key_down( 
                    event.key.keysym.sym );
                break;
            case SDL_KEYUP:
                bInput::get_singleton().call_event_key_up( 
                    event.key.keysym.sym );
                break;
            case SDL_QUIT:
                return is_running=false;
        }

    }
    
    return is_running;
}

void bSDLSystem::quit()
{
    is_running = false;
}

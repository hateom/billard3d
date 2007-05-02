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

#include "bsystem.h"

bPath           bSystem::path_sys;
bProfiler       bSystem::profiler_sys;
bVideo          bSystem::video_sys;
bDraw           bSystem::draw_sys;
bLogger         bSystem::log_sys;
bFontMgr        bSystem::font_sys;
bConfigReader   bSystem::config_sys;
bInput          bSystem::input_sys;
bMainLoop       bSystem::mainloop_sys;
bStateMachine   bSystem::statemachine_sys;

bool bSystem::init(int argc, char *argv[] )
{
    try {
        bTrace::init();
        profiler_sys.init();   
        //log_sys.set_state(true);
        log_sys.set_state(false);
        path_sys.init(argv[0]);
    } catch( ... ) {
        release();
        return false;
    }
    
    return true;
}

void bSystem::release()
{
    mainloop_sys.release();
    input_sys.release();
    
    bTrace::dump();
}

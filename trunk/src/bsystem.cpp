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
#include "blayermgr.h"
#include "bsincos.h"

#include <cstring>

#define IsArg(ARG) (strcmp( GetArgMgr.get(ARG), "1" ) == 0)

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
bArgMgr         bSystem::argmgr_sys;
bCamera         bSystem::camera_sys;

bool bSystem::init(int argc, char *argv[] )
{
    try {
        for( int i=1; i<argc; ++i ) {
            argmgr_sys.add_cfg( argv[i] );
        }
        bTrace::init();
        profiler_sys.init();   
        if( IsArg("verbose") ) {
            log_sys.set_state(true);
        }
        int res;
        if( GetArgMgr.get_int("shaders", &res) ) {
            bShader::set_enabled( res==1 );
        }
        path_sys.init(argv[0]);
		bLayerMgr::init();
        bSinCos::init();
    } catch( ... ) {
        release();
        return false;
    }
    
    return true;
}

void bSystem::release()
{
    mainloop_sys.release();
    bLayerMgr::release();
    input_sys.release();
    
    bTrace::dump();
    argmgr_sys.free();
}

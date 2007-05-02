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

#ifndef BSYSTEM_H
#define BSYSTEM_H

#include "bassert.h"
#include "bpath.h"
#include "btrace.h"
#include "bprofiler.h"
#include "bvideo.h"
#include "bdraw.h"
#include "blogger.h"
#include "bfontmgr.h"
#include "bconfigreader.h"
#include "binput.h"
#include "bsdlsystem.h"
#include "bmainloop.h"
#include "bstatemachine.h"
#include "bargmgr.h"

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bSystem
{
public:
    
    /**
     * Initializing function - must be called at the very beginning
     * @param argc main func argc argument
     * @param argv[] main func argv argument
     * @return true if all is ok
     */
    static bool init( int argc, char *argv[] );
    
    
    /**
     * Releases system resources - must be called before quiting
     */
    static void release();
    
public:
    static bPath            path_sys;
    static bProfiler        profiler_sys;
    static bVideo           video_sys;
    static bDraw            draw_sys;
    static bLogger          log_sys;
    static bFontMgr         font_sys;
    static bConfigReader    config_sys;
    static bInput           input_sys;
    static bSDLSystem       sdl_sys;
    static bMainLoop        mainloop_sys;
    static bStateMachine    statemachine_sys;
    static bArgMgr          argmgr_sys;
};

#endif

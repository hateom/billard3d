/***************************************************************************
 *   Copyright (C) 2007 by Tomasz Huczek                                   *
 *   tomasz.huczek@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "bsystem.h"
#include "bmainloop.h"
#include "bsimlogiclayer.h"
#include "bsimvideolayer.h"

//---------------------------------------------------------------------------------------------

int main( int argc, char* argv[] )
{
    if( !bSystem::init( argc, argv ) ) return -1;
    
    DBLOG( ">> Debug version\n" );
    
    try {
        
        bSystem::video_sys.setup(
            GetConfig.screen_w,
            GetConfig.screen_h,
            GetConfig.depth,
            GetConfig.full_screen
        );
        bSystem::draw_sys.create();
        bSystem::font_sys.init();

        bSystem::statemachine_sys.go_to( BS_SIMULATION );
        
        while( bSystem::sdl_sys.update() ) {
            bSystem::mainloop_sys.update();
            bSystem::video_sys.buffers();
        }

    } catch( bException & e ) {
        std::cout << e.format() << std::endl;
	} catch( ... ) {
		std::cout << "!! Unknown exception occured!" << std::endl;
	}
    
    bSystem::font_sys.release();
    bSystem::draw_sys.release();
    bSystem::video_sys.release();

	bSystem::release();
    
    DBLOG( ">> Finished (debug trace written to ./debug_log.txt)\n" );
    
    return 0;
}

//---------------------------------------------------------------------------------------------

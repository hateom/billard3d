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

#include <iostream>
#include "bdraw.h"
#include "bvideo.h"
#include "bvector.h"
#include "bassert.h"
#include "blogger.h"
#include "bfontmgr.h"
#include "bpath.h"
#include "btrace.h"

//---------------------------------------------------------------------------------------------

int main( int argc, char* argv[] )
{
    bPath path;
    bTrace::init();
        
    bVideo video;
    bDraw  graph;
    bLogger logger;
    bFontMgr fontMgr;
    
#ifdef DEBUG
    std::cout << ">> Debug version" << std::endl;
    try {
#endif
   
        logger.set_state(true);
        path.init(argv[0]);
        
        if( !video.setup() ) {
            return -1;
        }

        if( !graph.create() ) {
            video.release();
            return -2;
        }

        FontMgr.init();

        while( video.messages() ) {
            graph.draw();
            video.buffers();
        }

#ifdef DEBUG
    } catch( bUnknownException & ue ) {
        std::cout << ue.format() << std::endl;
    } catch( bException & e ) {
        std::cout << e.format() << std::endl;
	} catch( ... ) {
		std::cout << "!! Unknown exception occured!" << std::endl;
	}
#endif // DEBUG
    
    FontMgr.release();
    graph.release();
    video.release();
    
#ifdef DEBUG
    std::cout << ">> Finished." << std::endl;
#endif // DEBUG
    
    return 0;
}

//---------------------------------------------------------------------------------------------

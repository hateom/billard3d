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

int main( int argc, char* argv[] )
{
#ifdef DEBUG
    std::cout << ">> Debug version" << std::endl;
    try {
#endif
        bVideo video;
        bDraw  graph;
        
        if( !video.setup() ) {
            return -1;
        }

        if( !graph.create() ) {
            video.release();
            return -2;
        }

        while( video.messages() ) {
            graph.draw();
            video.buffers();
        }
        
        graph.release();
        video.release();

#ifdef DEBUG
    } catch( bException & e ) {
        std::cout << e.format() << std::endl;
    }
    std::cout << ">> Finished." << std::endl;
#endif // DEBUG
    
    return 0;
}
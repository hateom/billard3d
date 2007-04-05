/***************************************************************************
 *   Copyright (C) 2007 by Tomasz Huczek                                      *
 *   tomasz.huczek@gmail.com                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "bdraw.h"
#include "bvideo.h"

int main( int argc, char* argv[] )
{
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

    return 0;
}

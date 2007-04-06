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
#include "bvector.h"
#include <iostream>
#include <unistd.h>


using namespace std;

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
	sleep(0);
    }

    graph.release();
    video.release();
    
    bVector V1(1,1);
    bVector V2(2,2);
    bVector V3;
    V3 = V1 + V2;
    V3 = V3 - V2;
    cout << V1+V2 << endl;
    cout << V3 <<endl;
    cout << V3 - V1 << endl;
    
    return 0;
}

/***************************************************************************
 *   Copyright (C) 2007 by Tomasz Huczek   *
 *   tomasz.huczek@gmail.com   *
 ***************************************************************************/

#include "bvideo.h"

int main( int argc, char* argv[] )
{
    bVideo video;
    if( !video.setup() ) {
        return -1;   
    }
    
    
    while( video.messages() ) {
        video.draw();
    }
    
    video.release();

    return 0;
}


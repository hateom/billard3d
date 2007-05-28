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

#include "bcamera.h"
#include "bgl.h"
#include "bsincos.h"
#include <cmath>

bCamera::bCamera()
 : bSingleton<bCamera>()
{
    eye.x = 0.0;
    eye.y = 4.0;
    eye.z = 0.0;
    dest.x = 0.0;
    dest.y = 0.0;
    dest.z = 0.0;
    
    angle = 0.0;
}


bCamera::~bCamera()
{
}

void bCamera::look_at()
{
    gluLookAt( eye.x,  eye.y,  eye.z, 
               dest.x, dest.y, dest.z, 
               0.0, 1.0, 0.0 );
}

void bCamera::update()
{
    bVector3 de, dd;
    
    de = go_eye - eye;
    dd = go_dest - dest;
    
    eye += de/10.0;
    dest += dd/10.0;
}

double bCamera::get_distance(bVector3 vec)
{
    return eye.distance( vec );
}

void bCamera::set_top_view()
{
    go_dest = bVector3( 0.0, 1.0, -0.2 );
    go_eye  = bVector3( 0.0, 15.0, 0.0 );
}

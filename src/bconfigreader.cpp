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

#include "bconfigreader.h"

bConfigReader::bConfigReader()
{
    set_default();
}

bConfigReader::~bConfigReader()
{
}

bool bConfigReader::read_config(const char * filename)
{
    return true;
}

void bConfigReader::set_default()
{
    config.screen_w    = 800;
    config.screen_h    = 600;
    config.depth       =  32;
    config.full_screen = false;
}


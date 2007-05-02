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

#ifndef BCONFIGREADER_H
#define BCONFIGREADER_H

#include "bsingleton.h"
#include "bconfig.h"

#define GetConfig bConfigReader::get_singleton().config

/**
    @brief Configuration reader
    Reads configuration from file
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bConfigReader: public bSingleton<bConfigReader>
{
public:
    bConfigReader();
    ~bConfigReader();

    /**
        Reads configuration from file
        @param filename configuration file
        @returns true if everything is allright
    */
    bool read_config( const char * filename );
    
    /// set default configuration
    void set_default();
    
public:
    bConfig config;
};

#endif

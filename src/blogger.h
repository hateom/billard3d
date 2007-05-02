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

#ifndef BLOGGER_H
#define BLOGGER_H

#include "bsingleton.h"
#include "bassert.h"

#define BLOG bLogger::get_singleton().log

#ifdef DEBUG
#   define DBLOG BLOG
#else
#   define DBLOG( TEMP )
#endif

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bLogger : public bSingleton<bLogger>
{
public:
    bLogger();
    ~bLogger();

    /**
     * @param enabled enables logger to write into standard output
     */
    void set_state( bool enabled );
    
    
    /**
     * @param text outputs formatted string
     */
    void log( const char * text, ... );
    
private:
    bool on;
};

#endif

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

#include <bsingleton.h>

#define BLOG bLogger::get_Singleton().log

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bLogger : public bSingleton<bLogger>
{
public:
    bLogger();
    ~bLogger();

    void set_state( bool enabled );
    void log( const char * text, ... );
    
private:
    bool on;
};

#endif

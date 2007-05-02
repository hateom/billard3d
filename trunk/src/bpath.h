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

#ifndef B_PATH_H
#define B_PATH_H

#include <iostream>
#include <string>
#include "bsingleton.h"

#define GETPATH( NFILE ) bPath::get_singleton().get_full_path( NFILE )

/**
    @author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
 */
class bPath: public bSingleton<bPath>
{
public:
	bPath();
	~bPath();

	bool init( const char * argv0 );
	const char * get_full_path( const char * file ) const;

private:
	std::string dir;
	bool created;
	char separator;
};

#endif // B_PATH_H


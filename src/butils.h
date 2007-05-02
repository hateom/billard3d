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

#ifndef BUTILSBUTILS_H
#define BUTILSBUTILS_H

//---------------------------------------------------------------------------------------------

namespace bUtils {

//---------------------------------------------------------------------------------------------
    
/**
    Various utilities

	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/

//---------------------------------------------------------------------------------------------

/**
    Makes a string copy
    @param src input string to duplicate
    @returns a copy of input string
    @warning should be released by `delete []'
*/
char * scpy( const char * src );

}

//---------------------------------------------------------------------------------------------

#endif


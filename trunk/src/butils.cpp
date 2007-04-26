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

#include <cstring>
#include "butils.h"

//---------------------------------------------------------------------------------------------

namespace bUtils {

//---------------------------------------------------------------------------------------------
    
char * scpy( const char * src )
{
    if( src == NULL ) return NULL;
    char * dst;
    int len = strlen( src );
    dst = new char[len+1];
    strcpy( dst, src );
    return dst;
}

//---------------------------------------------------------------------------------------------

}

//---------------------------------------------------------------------------------------------

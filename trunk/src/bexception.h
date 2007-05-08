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

#ifndef BEXCEPTION_H
#define BEXCEPTION_H

#include "bstream.h"

/**
    @brief Default Exception class
    Defines standard exception class with useful methods
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bException 
{
public:
    bException( const char * file, int line, const char * expr, bStream & estrm );
    bException( const char * file, int line, const char * expr );
    bException( const bException & e );
    virtual ~bException();
    
    int get_line();
    const char * get_msg();
    const char * get_expr();
    const char * get_file();
    
    const char * format();
    
private:
    char * file, * expr, * msg;
    int line;
};

#endif

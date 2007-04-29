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

#ifndef BASSERT_H
#define BASSERT_H

//---------------------------------------------------------------------------------------------

#include <iostream>
#include "bexceptionstream.h"

//---------------------------------------------------------------------------------------------

#ifdef WIN32
#ifdef _DEBUG
#define DEBUG
#endif
#endif

#ifdef DEBUG
#define BASSERTM( EXPR, MSG ) if( !(EXPR) ) { \
            static bExceptionStream exp_strm;\
            exp_strm << MSG;\
            throw bException( \
            __FILE__, __LINE__, #EXPR, exp_strm ); }
#define BASSERT( EXPR ) if( !(EXPR) ) { throw bException( \
            __FILE__, __LINE__, #EXPR ); } 
#else // DEBUG
#define BASSERTM( EXPR, MSG )
#define BASSERT( EXPR )
#endif // DEBUG

//---------------------------------------------------------------------------------------------

/**
Assertion managing unit

	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bException {
public:
    bException( const char * file, int line, const char * expr, bExceptionStream & estrm );
    bException( const char * file, int line, const char * expr );
    ~bException();
    
    int get_line();
    const char * get_msg();
    const char * get_expr();
    const char * get_file();
    
    const char * format();
    
private:
    char * file, * expr, * msg;
    int line;
};

//---------------------------------------------------------------------------------------------

#endif
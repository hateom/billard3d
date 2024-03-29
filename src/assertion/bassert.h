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
#include "bexception.h"

//---------------------------------------------------------------------------------------------

#ifdef WIN32
#ifdef _DEBUG
#define DEBUG
#endif
#endif

/**
Assertion managing unit

    @author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
 */

#ifdef DEBUG
#define BASSERTM( EXPR, MSG ) if( !(EXPR) ) { \
            static bStream exp_strm;\
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

#endif

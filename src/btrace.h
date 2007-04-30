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

#ifndef BTRACE_H
#define BTRACE_H

#include "bassert.h"

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/

#ifdef DEBUG
#   define guard( FUNC ) \
        { \
            static const char * __FUNC_NAME__ = #FUNC; \
            try {
#   define unguard \
            } catch( bException & e ) { \
                bTrace::add_error_trace( __FUNC_NAME__ ); \
                throw e; \
            } catch( ... ) { \
                bTrace::add_error_trace( __FUNC_NAME__ ); \
                throw bUnknownException( __FILE__, __LINE__ ); \
            }\
        }
#else
#   define guard( TEMP )
#   define unguard
#endif

namespace bTrace {
    void init();
    void add_error_trace( const char * msg );
}

#endif

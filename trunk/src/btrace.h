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
    @brief Exceptions trace system
    Some macros used to create full tracing system. Every traced method
    should begins with @b guard and the last instruction must be @b unguard
    @warning unguard should be inserted after @b return statement!
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
                throw;\
            }\
        }
#else
#   define guard( TEMP )
#   define unguard
#endif

namespace bTrace {
    /**
        Initialize tracing system
    */
    void init();
    
    /**
        Report trace error
    */
    void add_error_trace( const char * msg );
    
    /**
        Dump trace information into file (debug mode only)
    */
	void dump();
}

#endif

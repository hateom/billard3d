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

#include "btrace.h"
#include "bpath.h"
#include "berrortrace.h"

namespace bTrace {

static bErrorTrace * errTrace = NULL;
    
void init()
{
    static bErrorTrace g_errTrace;
    errTrace = &g_errTrace;
}
    
void add_error_trace(const char * msg)
{
    if( errTrace ) errTrace->add_error( msg );
}

void dump()
{
#ifdef DEBUG
	if( errTrace ) errTrace->print_output();
#endif
}

}

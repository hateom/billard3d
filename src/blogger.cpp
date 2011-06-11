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

#include "blogger.h"
#include "btrace.h"

#include <iostream>

#include <cstdio>
#include <cstdarg>

bLogger::bLogger()
 : bSingleton<bLogger>(), on(false)
{
}

bLogger::~bLogger()
{
}

void bLogger::set_state(bool enabled)
{
    on = enabled;
}

void bLogger::log(const char * text, ...)
{
    guard(bLogger::log);
    
    if( !on ) return;
    
    static char buffer[512] = "";
    va_list al;
    
    ::va_start( al, text );
    ::vsprintf( buffer, text, al );
    ::va_end( al );
    
    std::cout << buffer;
    
    unguard;
}

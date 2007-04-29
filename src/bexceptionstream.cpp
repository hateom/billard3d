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

#include "bexceptionstream.h"
#include <string>

#define DEF_SIZE 1024

bExceptionStream::bExceptionStream() : size(DEF_SIZE) 
{ 
    buffer = new char[DEF_SIZE]; 
    memset(buffer,0,DEF_SIZE*sizeof(char));
}

bExceptionStream::bExceptionStream(int isize) : size(isize) 
{
    buffer = new char[isize]; 
    memset(buffer,0,isize*sizeof(char));
}

bExceptionStream::~bExceptionStream()
{ 
    delete [] buffer; 
    buffer = 0; 
    size = 0; 
}

bExceptionStream& bExceptionStream::operator <<( char * str )
{
    strcat(buffer, str); return *this; 
}

bExceptionStream& bExceptionStream::operator <<( const char * str ) 
{ 
    strcat(buffer, str); 
    return *this; 
}

bExceptionStream& bExceptionStream::operator <<( int val ) 
{ 
    static char temp[32]=""; 
    sprintf(temp,"%d",val);
    strcat(buffer,temp); 
    return *this; 
}

bExceptionStream& bExceptionStream::operator <<( float val ) 
{ 
    static char temp[32]=""; 
    sprintf(temp,"%f",val);
    strcat(buffer,temp); 
    return *this; 
}

bExceptionStream& bExceptionStream::operator <<( double val ) 
{ 
    static char temp[32]=""; 
    sprintf(temp,"%f",val);
    strcat(buffer,temp); 
    return *this; 
}

bExceptionStream& bExceptionStream::operator <<( char c ) 
{ 
    static char temp[32]=""; 
    sprintf(temp,"%c",c);
    strcat(buffer,temp); 
    return *this; 
}

const char * bExceptionStream::get_str() const 
{ 
    return buffer; 
}

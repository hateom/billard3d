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

#include "bstream.h"
#include <string>

#define DEF_SIZE 1024

bStream::bStream() : size(DEF_SIZE) 
{ 
    buffer = new char[DEF_SIZE]; 
    memset(buffer,0,DEF_SIZE*sizeof(char));
}

bStream::bStream(int isize) : size(isize) 
{
    buffer = new char[isize]; 
    memset(buffer,0,isize*sizeof(char));
}

bStream::~bStream()
{ 
    delete [] buffer; 
    buffer = 0; 
    size = 0; 
}

bStream& bStream::operator <<( char * str )
{
    strcat(buffer, str); return *this; 
}

bStream& bStream::operator <<( const char * str ) 
{ 
    strcat(buffer, str); 
    return *this; 
}

bStream& bStream::operator <<( int val ) 
{ 
    static char temp[32]=""; 
    sprintf(temp,"%d",val);
    strcat(buffer,temp); 
    return *this; 
}

bStream& bStream::operator <<( float val ) 
{ 
    static char temp[32]=""; 
    sprintf(temp,"%f",val);
    strcat(buffer,temp); 
    return *this; 
}

bStream& bStream::operator <<( double val ) 
{ 
    static char temp[32]=""; 
    sprintf(temp,"%f",val);
    strcat(buffer,temp); 
    return *this; 
}

bStream& bStream::operator <<( char c ) 
{ 
    static char temp[32]=""; 
    sprintf(temp,"%c",c);
    strcat(buffer,temp); 
    return *this; 
}

const char * bStream::get_str() const 
{ 
    return buffer; 
}


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

#ifndef BSTREAM_H
#define BSTREAM_H

/**
    @brief Stream message formatting class
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bStream
{
public:
    bStream();
    bStream(int isize);
    virtual ~bStream();

    bStream &operator <<( char * str );
    bStream &operator <<( const char * str );
    bStream &operator <<( int val );
    bStream &operator <<( float val );
    bStream &operator <<( double val );
    bStream &operator <<( char c );

    const char * get_str() const;
    
protected:
    char * buffer;
    int size;
};

#endif


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

#ifndef BEXCEPTIONSTREAM_H
#define BEXCEPTIONSTREAM_H

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bExceptionStream{
public:
    bExceptionStream();
    bExceptionStream(int isize);
    virtual ~bExceptionStream();

    bExceptionStream &operator <<( char * str );
    bExceptionStream &operator <<( const char * str );
    bExceptionStream &operator <<( int val );
    bExceptionStream &operator <<( float val );
    bExceptionStream &operator <<( double val );
    bExceptionStream &operator <<( char c );

    const char * get_str() const;
    
protected:
    char * buffer;
    int size;
};

#endif

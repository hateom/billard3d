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

#ifndef BLUTABLE_H
#define BLUTABLE_H

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bLUTable
{
public:
    bLUTable();
    ~bLUTable();
    
    bool create( int n, int m = -1, bool mirror=true );
    void release();
    void set( int x, int y, int val=1 );
    void clear( int x, int y );
    void clear();
    int  at( int x, int y ) const;
    
    inline int width() const { return w; }
    inline int height() const { return h; }
    
private:
    int   w, h;
    int * array;
    bool  mirr;
};

std::ostream& operator<<( std::ostream& out, const bLUTable & v );

#endif

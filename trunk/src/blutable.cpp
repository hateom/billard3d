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

#include "bassert.h"
#include "blutable.h"
#include "btrace.h"

bLUTable::bLUTable() : w(0), h(0), array(0), mirr(true)
{
}


bLUTable::~bLUTable()
{
    release();
}

bool bLUTable::create(int n, int m, bool mirror)
{
    guard(bLUTable::create);
    
    release();
    w = n;
    if( m == -1 ) h = n; else h = m;
    mirr = mirror;
    array = new int[w*h];
    clear();
    return true;
    
    unguard;
}

void bLUTable::release()
{
    guard(bLUTable::release);
    
    delete [] array;
    array = 0;
    w = h = 0;
    
    unguard;
}

int bLUTable::at(int x, int y) const
{
    guard(bLUTable::at);
    
    BASSERTM( x < w && y < h, "x("<<x<<"), y("<<y<<"), w("<<w<<"), h("<<h<<")\n" );
    return array[x+y*w];
    
    unguard;
}

void bLUTable::set(int x, int y,int val)
{
    guard(bLUTable::set);
    
    BASSERT( array != NULL );
    BASSERTM( x < w && y < h, "x("<<x<<"), y("<<y<<"), w("<<w<<"), h("<<h<<")\n" );
    if( mirr ) {
        array[y+x*w] = val;
    }
    array[x+y*w] = val;
    
    unguard;
}

void bLUTable::clear(int x, int y)
{
    guard(bLUTable::clear);
    
    BASSERT( array != NULL );
    BASSERTM( x < w && y < h, "x("<<x<<"), y("<<y<<"), w("<<w<<"), h("<<h<<")\n" );
    array[x+y*w] = 0;
    
    unguard;
}

void bLUTable::clear()
{
    guard(bLUTable::clear);
    
    BASSERT( array != NULL );
    memset( array, 0, sizeof(int)*w*h );
    
    unguard;
}


std::ostream & operator <<(std::ostream & out, const bLUTable & v)
{
    for( int i=0; i<v.width(); ++i ) {
        for( int j=0; j<v.height(); ++j ) {
            out << v.at( i, j ) << " ";
        }
        out << std::endl;
    }
    
    return out;
}

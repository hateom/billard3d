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

#include "berrortrace.h"
#include "bpath.h"

bErrorTrace::bErrorTrace()
{
}

bErrorTrace::~bErrorTrace()
{
    release();
}

bool bErrorTrace::add_error( const char * istr )
{
    if( !istr ) return( false );

    char * str = new char[strlen(istr)+1];
    strcpy( str, istr );
    list.push_back( str );

    return( true );
}

void bErrorTrace::print_output()
{
    if( list.size() == 0 ) return;

    FILE * file = fopen( GETPATH("debug_log.txt"), "w" );
    fprintf( file, "Debug Log - Error Tracer\n\n" );
    fprintf( file, "+Start Tracing\n" );
    int tab = 1;
    for( int i=(int)list.size()-1; i>=0; --i ) {
        fprintf( file, "+" );
        for(int k=0; k<tab; ++k) fprintf( file, "-" );
        fprintf( file, "%s", list[i]?list[i]:"???" );
        fprintf( file, "\n" );
        tab++;
    }
    fprintf( file, "+" );
    for(int k=0; k<tab; ++k) fprintf( file, "-" );
    fprintf( file, "Crash!!!" );
    fclose( file );
}

void bErrorTrace::release()
{
    for( unsigned int i=0; i<list.size(); ++i ) {
        delete [] list[i];
    }
    list.clear();
}

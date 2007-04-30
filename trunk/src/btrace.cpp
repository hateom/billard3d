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
#include <vector>

class bErrorTrace {
public:
    bErrorTrace() {}
    ~bErrorTrace()
    {
#ifdef DEBUG
        PrintOutput();
#endif
        Free();
    }

    bool AddError( const char * istr )
    {
        if( !istr ) return( false );

        char * str = new char[strlen(istr)+1];
        strcpy( str, istr );
        list.push_back( str );

        return( true );
    }

    void PrintOutput()
    {
        if( list.size() == 0 ) return;

        FILE * file = fopen( GETPATH("debug_log.txt"), "w" );
        fprintf( file, "Debug Log - Error Tracer\n\n" );
        fprintf( file, "+Start Tracing\n" );
        int tab = 1;
        for( size_t i=list.size()-1; i>=0; --i ) {
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

    void Free()
    {
        for( unsigned int i=0; i<list.size(); ++i )
        {
            delete [] list[i];
        }
        list.clear();
    }

private:
    std::vector<char*> list;
};

static bErrorTrace * errTrace = NULL;

namespace bTrace {

void init()
{
    static bErrorTrace g_errTrace;
    errTrace = &g_errTrace;
}
    
void add_error_trace(const char * msg)
{
    if( errTrace ) errTrace->AddError( msg );
}

}

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

#include <cstdio>
#include "butils.h"
#include "bexception.h"

bException::bException( const char * ifile, int iline, const char * iexpr, bStream & estrm )
    : line(iline)
{
    file = bUtils::scpy( ifile );
    expr = bUtils::scpy( iexpr );
    msg = bUtils::scpy( estrm.get_str() );
}

bException::bException( const char * ifile, int iline, const char * iexpr )
    : line(iline)
{
    file = bUtils::scpy( ifile );
    expr = bUtils::scpy( iexpr );
    msg = bUtils::scpy( "" );
}

bException::bException( const bException & e )
{
    file = bUtils::scpy( e.file );
    expr = bUtils::scpy( e.expr );
    msg  = bUtils::scpy( e.msg );
    line = e.line;
}

bException::~bException()
{
    delete [] file;
    delete [] expr;
    delete [] msg;
}

int bException::get_line()
{
    return line;
}

const char * bException::get_msg()
{
    return msg;
}

const char * bException::get_expr()
{
    return expr;
}

const char * bException::get_file()
{
    return file;
}

const char * bException::format()
{
    static char buffer[1024] = "";
    
    sprintf( buffer, "Exception occured in: %s\nat line: %d\nin expression: %s\n\n%s", 
             file, line, expr, msg?msg:"" );
    
    return buffer;
}

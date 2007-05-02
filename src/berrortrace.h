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

#ifndef BERRORTRACE_H
#define BERRORTRACE_H

#include <vector>

/**
    @brief Error tracking system. 
    Class saves call stack, and shows exception
    tree when program terminates.

	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bErrorTrace 
{
public:
    bErrorTrace();
    ~bErrorTrace();

    bool add_error( const char * istr );
    void print_output();
    void release();

private:
    std::vector<char*> list;
};

#endif

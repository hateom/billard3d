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


#ifndef B_ARG_MGR_H
#define B_ARG_MGR_H

#include <map>
#include <string>
#include "bsingleton.h"

#define GetArgMgr bArgMgr::get_singleton()
#define GetArg GetArgMgr.get

typedef std::map<std::string, std::string> str_map;
typedef std::pair<std::string, std::string> str_pair;

/**
    @brief Argument Manager
    @author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
 */
class bArgMgr: public bSingleton<bArgMgr>
{
public:
    int add_cfg( const char * cfg );
    const char * get( const char * option );
    bool get_int( const char * option, int * result );
    void free();

private:
    static str_map list;
};

#endif // B_ARG_MGR_H

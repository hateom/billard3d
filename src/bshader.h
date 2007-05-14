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

#ifndef BSHADERMGR_H
#define BSHADERMGR_H

#include "btypes.h"
#include "bgl.h"
#include "bcg.h"

/**
	@author Tomasz Huczek & Andrzej Jasiński <thuczek@gmail.com>
*/
class bShader
{
public:
    enum bProgram {
        B_VERTEX = 0x01,
        B_FRAGMENT = 0x02,
        B_BOTH = B_VERTEX | B_FRAGMENT
    };
public:
    bShader();
    virtual ~bShader();
    
    static bool is_supported();
    
    bool load_fragment( const char * filename );
    bool load_vertex( const char * filename );
    
    void bind( bProgram p = B_BOTH );
    void enable( bProgram p = B_BOTH );
    void disable( bProgram p = B_BOTH );
    
    void release();
    
    void set_matrices();
   
private:
    char * load_string( const char * filename );
    
    CGcontext vcontext;
    CGprogram vprogram;
    CGprofile vprofile;
    
    CGcontext fcontext;
    CGprogram fprogram;
    CGprofile fprofile;
    
    CGparameter mvp;
    CGparameter mv;
};

#endif

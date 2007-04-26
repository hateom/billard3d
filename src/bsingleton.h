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

#ifndef BSINGLETON_H
#define BSINGLETON_H

#include <iostream>
#include "bassert.h"

/**
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/

template <typename T>
class bSingleton
{
public:
    bSingleton() {
        BASSERT( single == NULL );
        
        int offs = (int)(T*)1 - (int)(bSingleton<T>*)(T*)1; 
        single = (T*)((int)this + offs);
    }
    
    virtual ~bSingleton() {
        BASSERT( single != NULL );
    }
    
    static T & get_Singleton() {
        BASSERT( single != NULL );
        return *single;
    }
    
    static T * get_singleton_ptr() {
        BASSERT( single != NULL );
        return single;
    }
    
private:
    static T * single;
};

template <typename T> T * bSingleton<T>::single = NULL;

#endif

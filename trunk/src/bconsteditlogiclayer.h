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

#ifndef BCONSTEDITLOGICLAYER_H
#define BCONSTEDITLOGICLAYER_H

#include "blogiclayer.h"

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bConstEditLogicLayer : public bLogicLayer
{
public:
    bConstEditLogicLayer();
    virtual ~bConstEditLogicLayer();

    void update();
    void on_key_down( uint32 key );
    void on_key_up( uint32 key );
    
    void init( bVideoLayer * );
    void release();

public:
	inline int get_menu_item() const { return menu_item; }

private:
	int menu_item;
};

#endif

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

#ifndef BOPTIONSLOGICLAYER_H
#define BOPTIONSLOGICLAYER_H

#include "blogiclayer.h"

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bOptionsLogicLayer : public bLogicLayer
{
public:
    bOptionsLogicLayer();
    virtual ~bOptionsLogicLayer();

    void update();
    void on_key_down( uint32 key );
    void on_key_up( uint32 key );
    
    void init( bVideoLayer * );
    void release();

public:
	inline int get_menu_item() const { return menu_item; }
	inline bool get_shaders_option() const { return shaders_option; }

private:
	int		menu_item;
	bool	shaders_option;
};

#endif

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

#include "boptionslogiclayer.h"
#include "bsdl.h"
#include "bsystem.h"

bOptionsLogicLayer::bOptionsLogicLayer()
 : bLogicLayer(true)
{
}


bOptionsLogicLayer::~bOptionsLogicLayer()
{
}

void bOptionsLogicLayer::update()
{
}

void bOptionsLogicLayer::on_key_down(uint32 key)
{
    switch(key) {
        case SDLK_ESCAPE:
            GetStateMachine.go_to( BS_PAUSE );
            break;
		case SDLK_s:
			shaders_option = !shaders_option;
			bShader::set_enabled( shaders_option );
			break;
		case SDLK_DOWN:
			if( menu_item < 1 ) menu_item++;
			break;
		case SDLK_UP:
			if( menu_item > 0 ) menu_item--;
			break;
		case SDLK_RETURN:
			if( menu_item == 1 ) GetStateMachine.go_to( BS_PAUSE );
			if( menu_item == 0 ) {
				shaders_option = !shaders_option;
				bShader::set_enabled( shaders_option );
			}
			break;
    }
}

void bOptionsLogicLayer::on_key_up(uint32 key)
{
}

void bOptionsLogicLayer::release()
{
}

void bOptionsLogicLayer::init( bVideoLayer * )
{
	menu_item = 0;
	shaders_option = bShader::is_enabled();
}

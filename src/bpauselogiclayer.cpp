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

#include "bpauselogiclayer.h"
#include "bsdl.h"
#include "bsystem.h"

bPauseLogicLayer::bPauseLogicLayer()
 : bLogicLayer(true)
{
}


bPauseLogicLayer::~bPauseLogicLayer()
{
}

void bPauseLogicLayer::update()
{
}

void bPauseLogicLayer::on_key_down(uint32 key)
{
    switch(key) {
        case SDLK_ESCAPE:
            GetStateMachine.go_to( BS_SIMULATION );
            break;
        case SDLK_q:
            GetStateMachine.go_to( BS_QUIT );
            break;
		case SDLK_o:
            GetStateMachine.go_to( BS_OPTIONS );
            break;
		case SDLK_DOWN:
			if( menu_item < 2 ) menu_item++;
			break;
		case SDLK_UP:
			if( menu_item > 0 ) menu_item--;
			break;
		case SDLK_RETURN:
			if( menu_item == 0 ) GetStateMachine.go_to( BS_SIMULATION );
			if( menu_item == 1 ) GetStateMachine.go_to( BS_OPTIONS );
			if( menu_item == 2 ) GetStateMachine.go_to( BS_QUIT );
			break;
    }
}

void bPauseLogicLayer::on_key_up(uint32 key)
{
}

void bPauseLogicLayer::release()
{
}

void bPauseLogicLayer::init( bVideoLayer * )
{
	menu_item = 0;
}

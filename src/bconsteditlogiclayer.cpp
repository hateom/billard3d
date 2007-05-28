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

#include "bconsteditlogiclayer.h"
#include "bsdl.h"
#include "bsystem.h"
#include "bconst.h"

bConstEditLogicLayer::bConstEditLogicLayer()
 : bLogicLayer(true)
{
}


bConstEditLogicLayer::~bConstEditLogicLayer()
{
}

void bConstEditLogicLayer::update()
{
}

void bConstEditLogicLayer::on_key_down(uint32 key)
{
    switch(key) {
        case SDLK_ESCAPE:
            GetStateMachine.go_to( BS_OPTIONS );
            break;
		case SDLK_DOWN:
			if( menu_item < 3 ) menu_item++;
			break;
		case SDLK_UP:
			if( menu_item > 0 ) menu_item--;
			break;
		case SDLK_RETURN:
            if( menu_item == 3 ) {
                GetStateMachine.go_to( BS_OPTIONS );
            }
			break;
        case SDLK_LEFT:
            if( menu_item == 0 ) {
                bConst::set_frict_f( bConst::get_frict_f() - 0.001 );
            }
            if( menu_item == 1 ) {
                bConst::set_spring_f( bConst::get_spring_f() - 0.01 );
            }
			if( menu_item == 2 ) {
                bConst::set_epsilon( bConst::get_epsilon() - 0.0000001 );
			}
            break;
        case SDLK_RIGHT:
            if( menu_item == 0 ) {
                bConst::set_frict_f( bConst::get_frict_f() + 0.001 );
            }
            if( menu_item == 1 ) {
                bConst::set_spring_f( bConst::get_spring_f() + 0.01 );
            }
			if( menu_item == 2 ) {
                bConst::set_epsilon( bConst::get_epsilon() + 0.0000001 );
			}
            break;
    }
}

void bConstEditLogicLayer::on_key_up(uint32 key)
{
}

void bConstEditLogicLayer::release()
{
}

void bConstEditLogicLayer::init( bVideoLayer * )
{
	menu_item = 0;
}

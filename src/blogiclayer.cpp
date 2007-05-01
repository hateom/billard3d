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

#include "blogiclayer.h"
#include "binput.h"

bLogicLayer::bLogicLayer(bool exclusiv) : exclusive(exclusiv)
{
    bInput::get_singleton().register_listener(this);
}

bLogicLayer::~bLogicLayer()
{
    bInput::get_singleton().unregister_listener(this);
}

bool bLogicLayer::is_exclusive() const
{
    return exclusive;
}

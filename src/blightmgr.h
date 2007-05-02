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
 
#ifndef B_LIGHT_MGR_H
#define B_LIGHT_MGR_H

/**
    @brief Light Manager
    @author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
 */
class bLightMgr
{
public:
	static void set_defaults();
	static void on();
	static void off();

protected:
	static float lamb[4];
    static float ldif[4];
	static float lpos[4];
};

#endif // B_LIGHT_MGR_H

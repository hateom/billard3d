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


#ifndef B_FONT_MGR_H
#define B_FONT_MGR_H

#include "bsingleton.h"
#include "bfont.h"

#define B_DEF_FONT   0x01
#define B_SMALL_FONT 0x02

#define PRINT  bFontMgr::get_singleton().get_font().writef
#define PRINTS bFontMgr::get_singleton().get_font(B_SMALL_FONT).writef
#define FontMgr bFontMgr::get_singleton()

/**
    @brief Font manager class
    Managing fonts system
    @author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
 */
class bFontMgr: public bSingleton<bFontMgr>
{
public:
	bFontMgr();
	~bFontMgr();

    /// loads default font
	bool init();
	void release();

	/// @param font musb be B_DEF_FONT or B_SMALL_FONT
	bFont & get_font( int font = B_DEF_FONT );

private:
	bFont def;
	bFont def_small;

	bool  def_loaded;
};

#endif // B_FONT_MGR_H

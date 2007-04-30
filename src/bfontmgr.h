#ifndef __B_FONT_MGR_H__
#define __B_FONT_MGR_H__

#include "bsingleton.h"
#include "bfont.h"

#define B_DEF_FONT   0x01
#define B_SMALL_FONT 0x02

#define PRINT  bFontMgr::get_singleton().get_font().writef
#define PRINTS bFontMgr::get_singleton().get_font(B_SMALL_FONT).writef
#define FontMgr bFontMgr::get_singleton()

class bFontMgr: public bSingleton<bFontMgr>
{
public:
	bFontMgr();
	~bFontMgr();

    //! loads default font
	bool init();
	void release();

	//! @param font musb be B_DEF_FONT or B_SMALL_FONT
	bFont & get_font( int font = B_DEF_FONT );

private:
	bFont def;
	bFont def_small;

	bool  def_loaded;
};

#endif // __B_FONT_MGR_H__

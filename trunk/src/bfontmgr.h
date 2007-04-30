#ifndef __B_FONT_MGR_H__
#define __B_FONT_MGR_H__

#include "bsingleton.h"
#include "bfont.h"

#define PRINT bFontMgr::get_singleton().get_font().writef
#define FontMgr bFontMgr::get_singleton()

class bFontMgr: public bSingleton<bFontMgr>
{
public:
	bFontMgr();
	~bFontMgr();

	bool load_default();
	void release();

	bFont & get_font();

private:
	bFont def;
    bool  def_loaded;
};

#endif // __B_FONT_MGR_H__

#include "bfontmgr.h"

bFontMgr::bFontMgr() : bSingleton<bFontMgr>()
{
}

bFontMgr::~bFontMgr()
{
	release();
}

bool bFontMgr::load_default( const char * filename )
{
	return def.load( filename );
}

void bFontMgr::release()
{
	def.release();
}

bFont & bFontMgr::get_font()
{
	return def;
}

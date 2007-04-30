#include "bfontmgr.h"
#include "btrace.h"

bFontMgr::bFontMgr() : bSingleton<bFontMgr>()
{
}

bFontMgr::~bFontMgr()
{
	release();
}

bool bFontMgr::load_default( const char * filename )
{
    guard(bFontMgr::load_default);
    
	return def.load( filename );
    
    unguard;
}

void bFontMgr::release()
{
    guard(bFontMgr::release);
    
	def.release();
    
    unguard;
}

bFont & bFontMgr::get_font()
{
	return def;
}

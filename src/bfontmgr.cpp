#include "bfontmgr.h"
#include "btrace.h"
#include "font_default.h"
#include "blogger.h"

bFontMgr::bFontMgr() : bSingleton<bFontMgr>(), def_loaded(false)
{
}

bFontMgr::~bFontMgr()
{
	release();
}

bool bFontMgr::load_default()
{
    guard(bFontMgr::load_default);
    
	def_loaded = def.load( (uint8*)font_default_data.pixel_data, 
                           font_default_data.width,
                           font_default_data.height );
    return def_loaded;
    
    unguard;
}

void bFontMgr::release()
{
    guard(bFontMgr::release);
    
	if( def_loaded ) {
        def.release();
        def_loaded = false;
    }
    
    unguard;
}

bFont & bFontMgr::get_font()
{
    guard(bFontMgr::get_font);
    
    BASSERT( def_loaded );
	return def;
    
    unguard;
}

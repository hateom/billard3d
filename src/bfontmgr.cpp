#include "bfontmgr.h"
#include "btrace.h"
#include "blogger.h"

#include "font01.h"
#include "font02.h"

bFontMgr::bFontMgr() : bSingleton<bFontMgr>(), def_loaded(false)
{
}

bFontMgr::~bFontMgr()
{
	release();
}

bool bFontMgr::init()
{
    guard(bFontMgr::load_default);
    
	if( !def.load( (uint8*)font_default_data, 
		font_default_width,
		font_default_height )) return false;

	if( !def_small.load( (uint8*)font_small_data, 
		font_small_width,
		font_small_height )) return false;

    return def_loaded=true;
    
    unguard;
}

void bFontMgr::release()
{
    guard(bFontMgr::release);
    
	if( def_loaded ) {
        def.release();
		def_small.release();
        def_loaded = false;
    }
    
    unguard;
}

bFont & bFontMgr::get_font( int font )
{
    guard(bFontMgr::get_font);
    
    BASSERT( def_loaded );
	
	if( font == B_DEF_FONT ) {
		return def;
	} else if( font == B_SMALL_FONT ) {
		return def_small;
	} else {
		BASSERTM( 0, "Wrong font type!" );
	}
    
    unguard;
}

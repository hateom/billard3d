#include "bfontmgr.h"
#include "btrace.h"
#include "blogger.h"

#include "font01.h"
#include "font02.h"
#include "font03.h"

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
    
	if( !def.load( (uint8*)bFontData::font_default_data, 
        bFontData::font_default_width,
        bFontData::font_default_height )) return false;

    if( !def_small.load( (uint8*)bFontData::font_small_data, 
        bFontData::font_small_width,
        bFontData::font_small_height )) return false;
    
    if( !def_big.load( (uint8*)bFontData::font_big_data, 
        bFontData::font_big_width,
        bFontData::font_big_height )) return false;

    return def_loaded=true;
    
    unguard;
}

void bFontMgr::release()
{
    guard(bFontMgr::release);
    
	if( def_loaded ) {
        def.release();
		def_small.release();
        def_big.release();
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
    } else if( font == B_BIG_FONT ) {
        return def_big;
	} else {
		BASSERTM( 0, "Wrong font type!" );
	}
    
    unguard;
}

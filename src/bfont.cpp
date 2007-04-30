#include "bfont.h"
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include "bsdl.h"
#include "bassert.h"
#include "btrace.h"

bFont::bFont() : coords(NULL), widths(NULL), font_data(NULL)
{
}

bFont::~bFont()
{
	release();
}

void bFont::release()
{
    guard(bFont::release);
	
    release_font();
	texture.release();
    
    unguard;
}

uint32 bFont::char_width( uint8 character )  const
{
	return( (uint32)widths[character].size );
}

uint32 bFont::char_height( uint8 character ) const
{
	return( f_height );
}

uint32 bFont::str_width( const char * str )  const
{
    guard(bFont::str_width);
    
	uint16 length = 0;
	uint16 len = (uint16)strlen( str );
	uint16 max = 0;

	for( uint16 i=0; i<len; ++i )
	{
		if( str[i] == '\n' )
		{
			if( length > max ) max = length;
			length = 0;
			continue;
		}
		length += widths[str[i]].size;
	}

	if( length > max ) max = length;

	return( (uint32)max );
    
    unguard;
}

uint32 bFont::str_height( const char * str ) const
{
    guard(bFont::str_height);
    
	int32 n = 1;
	int32 len = (int32)strlen( str );

	for( int i=0; i<len; ++i )
	{
		if( str[i] == '\n' ) n++;
	}

	return( f_height*n );
    
    unguard;
}

bool bFont::load( const char * filename )
{
    guard(bFont::load);
    
	if( !texture.load( filename ) )
	{
		return( false );
	}

	if( !build_font() )
	{
		release();
		return( false );
	}

	return( true );
    
    unguard;
}

bool bFont::load(uint8 * data, uint32 w, uint32 h)
{
    guard(bFont::load);
    
    if( !texture.load( data, w, h ) )
    {
        return( false );
    }

    if( !build_font() )
    {
        release();
        return( false );
    }

    return( true );
    
    unguard;
}

void bFont::set_size( float scale )
{
    guard(bFont::set_size);
    
	size = scale;

	for( int i=0; i<256; ++i )
	{
		widths[i].sizeo = (int)(widths[i].size*size);
	}

	ysiz = (int)(((float)f_height)*size);
    
    unguard;
}

void bFont::writef( uint32 x, uint32 y, uint32 mode, const char * fmt, ... ) const
{
    guard(bFont::writef);
    
	static char str[1024];

	va_list al;
	va_start( al, fmt );
	vsprintf( str, fmt, al );
	va_end( al );

	write( x, y, mode, str );
    
    unguard;
}

void bFont::write( uint32 x, uint32 y, uint32 mode, const char * str ) const
{
    guard(bFont::write);
    
	BASSERT( ( coords != NULL ) && ( widths != NULL ) );

	uint32 len = (uint32)strlen( str );
	int32 orgx = x;
	char c;

	glPushAttrib( GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT );
	glEnable( GL_BLEND );
	glBlendFunc( (mode==B_FONT_DARK)?GL_ZERO:GL_ONE, GL_ONE_MINUS_SRC_COLOR );

	texture.bind();

	glBegin( GL_TRIANGLE_STRIP );
	for( uint32 i=0; i<len; ++i )
	{
		c = str[i];
		if( c == '\n' )
		{
			glEnd();
			x = orgx;
			y += ysiz;
			glBegin( GL_TRIANGLE_STRIP );
		}
		else
		{
			glTexCoord2f( coords[c].sx, coords[c].sy ); glVertex2i(					x,      y );
			glTexCoord2f( coords[c].sx, coords[c].ey ); glVertex2i(					x, y+ysiz );
			glTexCoord2f( coords[c].ex, coords[c].sy ); glVertex2i( x+widths[c].sizeo,	    y );
			glTexCoord2f( coords[c].ex, coords[c].ey ); glVertex2i( x+widths[c].sizeo, y+ysiz );
			x += widths[c].sizeo;
		}
	}
	glEnd();

	glPopAttrib();
    
    unguard;
}

bool bFont::build_font()
{
    guard(bFont::build_font);
    
	uint32 index = 0;
	
	f_count  = 256;
	f_width  = texture.width()  >> 4;  // div 16
	f_height = texture.height() >> 4;  // div 16

	widths = new font_width[f_count];

	font_data = new uint8[f_width*f_height];

	for( uint32 y=0; y<16; ++y )
	{
		for( uint32 x=0; x<16; x++ )
		{
			get_font_width( x, y, &widths[index++] );
		}
	}

	delete [] font_data;
	font_data = NULL;

	coords = new font_coords[f_count];
	float fx = 0.0f, fy = 0.0f;
	float fsx = 0.0f, ffw = 0.0f;
	uint32 i = 0;

	for( uint32 y=0; y<16; ++y )
	{
		fy = (float)y;
		for( int x=0; x<16; x++ )
		{
			fx = (float)x;

			fsx = widths[i].start;
			ffw = widths[i].fsize;

			coords[i].sx = (fx+fsx)/16.0f;
			coords[i].sy = fy/16.0f;
			coords[i].ex = (fx+fsx+ffw)/16.0f;
			coords[i].ey = (fy+1.0f)/16.0f;
			i++;
		}
	}

	set_size( 1.0f );

	return( true );
    
    unguard;
}

void bFont::release_font()
{
    guard(bFont::release_font);
    
	if( coords != NULL )
	{
		delete [] coords;
		coords = NULL;
	}

	if( widths != NULL )
	{
		delete [] widths;
		widths = NULL;
	}
    
    unguard;
}

bool bFont::get_font_width( uint32 fx, uint32 fy, font_width * fw )
{
    guard(bFont::get_font_width);
    
	get_font_data( fx, fy, font_data );

	int start = -1;
	int end   = -1;
	bool flag = false;

	for( int x=0; x<f_width; ++x )
	{
		flag = false;
		for( int y=0; y<f_height; ++y )
		{
			if( font_data[x+(y*f_width)] != 0 )
			{
				start = x-1;
				if( start < 0 ) start = 0;
				flag = true;
			}
		}
		if( flag ) break;
	}

	if( !flag ) start = 0;

	for( uint32 x=f_width-1; x>=0; --x )
	{
		flag = false;
		for( int y=0; y<f_height; ++y )
		{
			if( font_data[x+(y*f_width)] != 0 )
			{
				end = x+1;
				if( end >= f_width ) end = f_width-1;
				flag = true;
			}
		}
		if( flag ) break;
	}

	if( !flag ) end = 0;

	if( (fx+fy*16) == 32 ) // SPACE
	{
		start = 0;
		end = 7;
	}

	fw->start = ((float)start)/((float)f_width);
	fw->end   = ((float)end)/((float)f_width);
	fw->fsize = fw->end-fw->start;
	fw->size = end-start;

	return( true );
    
    unguard;
}

uint8 & bFont::font_buffer( uint32 x, uint32 y )
{
    guard(bFont::font_buffer);
    
	uint8 * data = texture.data();
	BASSERT( ( x < texture.width() ) && ( y < texture.height() ) );

	return( data[3*(x+(y*texture.width()))] );
    
    unguard;
}

bool bFont::get_font_data( uint32 px, uint32 py, uint8 * b )
{
    guard(bFont::get_font_data);
    
	uint32 sx = px*f_width;
	uint32 sy = py*f_height;

	uint32 index = 0L;

	for( uint32 y=sy; y<sy+f_height; ++y )
	{
		for( uint32 x=sx; x<sx+f_width; ++x )
		{
			b[index] = font_buffer( x, y );
			index++;
		}
	}

	return( true );
    
    unguard;
}

void bFont::update()
{
    guard(bFont::update);
    
	release_font();
	build_font();
    
    unguard;
}

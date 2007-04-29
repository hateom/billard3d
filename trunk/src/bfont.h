#ifndef __B_FONT_H__
#define __B_FONT_H__

#include "btypes.h"
#include "btexture.h"

#define DG_FONT_LIGHT 0x00
#define DG_FONT_DARK  0x01

class bFont
{
	struct font_coords { float sx, sy, ex, ey; };
	struct font_width  { float start, end, fsize; int size; int sizeo; };

public:
	bFont();
	virtual ~bFont();

	bool load( const char * filename );
	void release();

	//! Updates fonts metrics. It must be called after calling Create() method!
	void update();

	uint32 char_width( uint8 character )  const;
	uint32 char_height( uint8 character ) const;
	uint32 str_width( const char * str )  const;
	uint32 str_height( const char * str ) const;
	void set_size( float scale );
	inline float get_size() const { return( size ); }
	void writef( uint32 x, uint32 y, uint32 mode, const char * fmt, ... ) const;
	void write( uint32 x, uint32 y, uint32 mode, const char * str ) const;

private:
	bool build_font();
	void release_font();

	bool  get_font_data( uint32 x, uint32 y, uint8 * b );
	uint8 & font_buffer( uint32 x, uint32 y );
	bool  get_font_width( uint32 x, uint32 y, font_width * fw );

	font_coords *	coords;
	font_width	*	widths;
	uint8		*	font_data;

	int	f_width;
	int	f_height;
	int	f_count;
	int	ysiz;

	float	size;
	bTexture texture;
};

#endif // __B_FONT_H__


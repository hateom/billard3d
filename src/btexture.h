#ifndef __B_TEXTURE_H__
#define __B_TEXTURE_H__

#include "btypes.h"
#include "bassert.h"

struct SDL_Surface;

class bTexture {
public:
	bTexture();
	bTexture( const char * filename );
	~bTexture();

	bool load( const char * filename );
    bool load( uint8 * data, uint32 w, uint32 h );
    
	void release();
	void bind() const;

	uint32 width() const;
	uint32 height() const;
	uint8 * data() const;

protected:
    void build_texture( SDL_Surface * s );
    
	SDL_Surface * surface;
	unsigned int tex_id;
};

#endif // __B_TEXTURE_H__

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
	void release();
	void bind() const;

	uint32 width() const;
	uint32 height() const;
	uint8 * data() const;

protected:
	SDL_Surface * surface;
	unsigned int tex_id;
};

#endif // __B_TEXTURE_H__

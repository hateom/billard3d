/***************************************************************************
 *   Copyright (C) 2007 by                                       *
 *                                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef B_TEXTURE_H
#define B_TEXTURE_H

#include "btypes.h"
#include "bassert.h"

struct SDL_Surface;

/**
    @brief Texture object
    Class used for loading images into OpenGL textures
    @author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
 */
class bTexture 
{
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

#endif // B_TEXTURE_H

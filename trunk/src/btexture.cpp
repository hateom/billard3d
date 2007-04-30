#include "btexture.h"
#include "bassert.h"
#include "bsdl.h"
#include "btrace.h"

bTexture::bTexture() : surface(0), tex_id(0)
{
}

bTexture::bTexture( const char * filename )
{
	bool flag;
	flag = load( filename );
	BASSERTM( flag == true, "Could not load texture from file: " << filename );
}

bTexture::~bTexture()
{
	release();
}

bool bTexture::load( const char * filename )
{
    guard(bTexture::load);
    
	surface = SDL_LoadBMP(filename);
	if( !surface ) return false;

	/* Standard OpenGL texture creation code */
	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

	glGenTextures( 1, &tex_id );
	glBindTexture( GL_TEXTURE_2D, tex_id );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

	gluBuild2DMipmaps(GL_TEXTURE_2D,3,surface->w, surface->h,GL_BGR_EXT,
		GL_UNSIGNED_BYTE, surface->pixels );

	return true;
    
    unguard;
}

void bTexture::bind() const
{
	glBindTexture( GL_TEXTURE_2D, tex_id );
}

void bTexture::release()
{
    guard(bTexture::release);
    
	if( surface != 0 ) {
		SDL_FreeSurface( surface );
		glDeleteTextures( 1, &tex_id );
		tex_id = 0;
		surface = NULL;
	}
    
    unguard;
}

uint32 bTexture::width() const 
{ 
    guard(bTexture::width);
    
	BASSERT( surface ); 
	return surface->w;
     
    unguard;
}

uint32 bTexture::height() const 
{ 
    guard(bTexture::height);
    
	BASSERT( surface ); 
	return surface->h; 
    
    unguard;
}

uint8 * bTexture::data() const
{
    guard(bTexture::data);
    
	BASSERT( surface );
	return (uint8*)surface->pixels;
    
    unguard;
}

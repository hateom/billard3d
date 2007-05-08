#include "btexture.h"
#include "bassert.h"
#include "bsdl.h"
#include "btrace.h"
#include "blogger.h"

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

	build_texture( surface );

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

bool bTexture::load(uint8 * data, uint32 w, uint32 h)
{
    guard(bTexture::load);
    
    surface = SDL_CreateRGBSurfaceFrom( data, w, h, 24, w*3, 
                    0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 );
    
    if( !surface ) return false;

    build_texture( surface );

    return true;
    
    unguard;
}

void bTexture::build_texture(SDL_Surface * s)
{
    guard(bTexture::build_texture);
    
    BASSERT( s != NULL );
    
    glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

    glGenTextures( 1, &tex_id );
    glBindTexture( GL_TEXTURE_2D, tex_id );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

//	if( compression_allowed() ) {
//		glTexImage2D( GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, s->w, s->h, 0,
//		GL_RGB, GL_UNSIGNED_BYTE, s->pixels);
//		BLOG( ":: creating compressed texture\n" );
//	} else {
		gluBuild2DMipmaps(GL_TEXTURE_2D,3,s->w, s->h,GL_BGR_EXT, GL_UNSIGNED_BYTE, s->pixels );
//	}
    
    unguard;
}

bool bTexture::compression_allowed()
{
	return glewIsExtensionSupported("GL_EXT_texture_compression_s3tc") == TRUE;
}

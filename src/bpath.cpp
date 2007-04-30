#include "bassert.h"
#include "bpath.h"
#include "btrace.h"

bPath::bPath() : bSingleton<bPath>(), dir(""), created(false), separator('\\')
{
}

bPath::~bPath()
{
}

bool bPath::init( const char * buffer )
{
    guard(bPath::init);
    
	char mdir[1024] = "";

	for( size_t i=strlen(buffer)-1; i>0; --i )
	{
		if( buffer[i] == '\\' || buffer[i] == '/' )
		{
			strncpy( mdir, buffer, i );
			mdir[i] = '\0';
			dir = mdir;
			separator = buffer[i];

			return( created = true );
		}
	}

	return( false );
    
    unguard;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]

const char * bPath::get_full_path( const char * file ) const
{
    guard(bPath::get_full_path);
    
	BASSERT( created == true );
	if( !created ) return( file );
	static char temp[1024] = "";

	sprintf( temp, "%s%c%s", dir.c_str(), separator, file );

	return( temp );
    
    unguard;
}


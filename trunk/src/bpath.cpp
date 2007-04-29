#include "bassert.h"
#include "bpath.h"

bPath::bPath() : bSingleton<bPath>(), dir(""), created(false), separator('\\')
{
}

bPath::~bPath()
{
}

bool bPath::init( const char * buffer )
{
	char mdir[1024] = "";

	for( int i=strlen(buffer)-1; i>0; --i )
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
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]

const char * bPath::get_full_path( const char * file ) const
{
	BASSERT( created == true );
	if( !created ) return( file );
	static char temp[1024] = "";

	sprintf( temp, "%s%c%s", dir.c_str(), separator, file );

	return( temp );
}

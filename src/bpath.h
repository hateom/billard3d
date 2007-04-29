#ifndef __B_PATH_H__
#define __B_PATH_H__

#include <iostream>
#include <string>
#include "bsingleton.h"

class bPath: public bSingleton<bPath>
{
public:
	bPath();
	~bPath();

	bool init( const char * argv0 );
	const char * get_full_path( const char * file ) const;

private:
	std::string dir;
	bool created;
	char separator;
};


#define GETPATH( NFILE ) bPath::get_singleton().get_full_path( NFILE )

#endif // __B_PATH_H__

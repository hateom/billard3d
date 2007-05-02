#include "bargmgr.h"
#include "butils.h"
#include <stdio.h>
#include <string.h>
#include <sstream>

str_map bArgMgr::list;

int bArgMgr::add_cfg( const char * cfg )
{
    char * ptr = bUtils::scpy(cfg);
    char * value;

    if( ptr[0] != '-' || ptr[1] != '-' ) return -1;
    
    ptr += 2;

    value = strstr( ptr, "=" );
    if( value != NULL )
    {
        value++;
        ptr[ value - ptr -1 ] = '\0';
    }
    else
    {
        value = "1";
    }

    list.insert( str_pair( std::string(ptr), std::string(value) ) );
    delete [] ( ptr-2 );

    return 0;
}

const char * bArgMgr::get( const char * str )
{
    static char buffer[1024] = "";
    std::string out = list[std::string(str)];
    strcpy( buffer, out.c_str() );
    return buffer;
}

void bArgMgr::free()
{
    list.clear();
}

bool bArgMgr::get_int( const char * str, int * result )
{
    BASSERTM( str != NULL && result != NULL, "Empty arguments" );

    std::string out = list[std::string(str)];
    std::istringstream in( out ); 
    int rc; 

    if( out == "" ) return false;

    if( in >> rc )
    {
        *result= rc;
    }
    else
    {
        return false;
    }

    return true;
}


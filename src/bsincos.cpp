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

#include <cmath>
#include "bsincos.h"
#include "bconst.h"
#include "blogger.h"

double bSinCos::LUT_c[SIN_TABLE_SIZE];
double bSinCos::LUT_s[SIN_TABLE_SIZE];

void bSinCos::init()
{
    double arg;

    for( int i=0; i<SIN_TABLE_SIZE; ++i ) {
        arg = ((double)i*B_2PI)/(double)SIN_TABLE_SIZE;
        LUT_s[i] = (double)sinf( (float)arg ); //~ ?
        LUT_c[i] = (double)cosf( (float)arg ); //~ ?
    }
}

double bSinCos::sin( double a )
{
    return LUT_s[ iround(a * 651.8986469) & SIN_TABLE_BITMASK ];
}

double bSinCos::cos( double a )
{
    return LUT_c[ iround(a * 651.8986469) & SIN_TABLE_BITMASK ];
}

int bSinCos::iround_down( double a ) 
{
    return iround( std::floor( a ) );
}

int bSinCos::iround_up( double a )
{
    return iround( std::ceil( a ) );
}

#if (defined _MSC_VER) && (defined __i386__)

//MSVC version (x86 only)
int bSinCos::iround( double a )
{
    int r; 
    __asm fld a   ;
    __asm fistp r ;
    return r;
}

#elif (defined __GNUC__) && (defined __i386__)
//gcc version (x86 only)
int bSinCos::iround( double a ) 
{
	int r;
	__asm__ __volatile__( 
		"fldl %1    \n\t"
		"fistpl %0  \n\t"
		: "=m" (r)
		: "m" (a)
	);
	return r;
}

#endif

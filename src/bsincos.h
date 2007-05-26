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

#ifndef BSINCOS_H
#define BSINCOS_H

#include <cmath>

#define NO_LUT_SINCOS

#define SIN_TABLE_SIZE		4096
#define SIN_TABLE_BITMASK	4095

#if !defined(NO_LUT_SINCOS)
#define bSin( A ) bSinCos::sin( A )
#define bCos( A ) bSinCos::cos( A )
#else
#define bSin( A ) sin( A )
#define bCos( A ) cos( A )
#endif

/**
    @brief Sine & cosine LUT
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/

class bSinCos
{
public:
    static void   init() {}
/*    
    static double sin( double a );
    static double cos( double a );

    static int iround( double a );
    static int iround_up( double a );
    static int iround_down( double a );

private:
    static double LUT_s[SIN_TABLE_SIZE];
    static double LUT_c[SIN_TABLE_SIZE];
*/
};

#endif 

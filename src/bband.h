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

#ifndef BBAND_H
#define BBAND_H

//---------------------------------------------------------------------------------------------

#include "bvector.h"

//---------------------------------------------------------------------------------------------

/**
	@author Tomasz Huczek & Andrzej Jasi�ski <thuczek@gmail.com>
*/
class bBand {
public:
    typedef enum band_piece {
        bNone, bSide, bEdge1, bEdge2
    };
public:
    bBand();
    bBand( bVector p1, bVector p2 );
    ~bBand();

    void draw();
    double distance( bVector pt ) const;
    band_piece is_within( bVector pt, double rad );
    
    void recalc();
    void set_points( bVector ip1, bVector ip2 );
    inline bVector get_p1() const { return p1; }
    inline bVector get_p2() const { return p2; }
    
protected:
    bVector p1, p2;
    double a, b, c, det;
};

//---------------------------------------------------------------------------------------------

#endif
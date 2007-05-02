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

#include "bvector.h"

/**
    @brief Board band object
    This class represents a board band, and implements some useful methods.
	@author Tomasz Huczek & Andrzej Jasiñski <thuczek@gmail.com>
*/
class bBand 
{
public:
    /// defines the area of collision
    typedef enum band_piece {
        bNone, bSide, bEdge1, bEdge2
    };
    
public:
    bBand();
    bBand( bVector p1, bVector p2 );
    ~bBand();

    /// draws a band
    void draw();
    
    /// @returns distance from vector @b pt
    double distance( bVector pt ) const;
    
    /// @returns area where collision occured
    band_piece is_within( bVector pt, double rad );
    
    /// recalculates parameters
    /// @warning must be called when p1 and p2 changes
    void recalc();
    
    /// set band position
    void set_points( bVector ip1, bVector ip2 );
    
    /// @returns band point 1
    inline bVector get_p1() const { return p1; }
    
    /// @returns band point 1
    inline bVector get_p2() const { return p2; }
    
protected:
    /// two edges of the band
    bVector p1, p2;
    
    /// parameters
    double a, b, c, det;
};

//---------------------------------------------------------------------------------------------

#endif

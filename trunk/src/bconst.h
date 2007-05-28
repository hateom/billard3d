/***************************************************************************
 *   Copyright (C) 2007 by Tomasz Huczek                                      *
 *   tomasz.huczek@gmail.com                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef BCONST_H
#define BCONST_H

/**
    @brief Constants
	@author Tomasz Huczek <tomasz.huczek@gmail.com>
*/

#define B_PI  (3.141592653589793238462)
#define B_2PI (6.283185307179586476925)

#define DEF_FRICT_F   0.005
#define DEF_SPRING_F  0.2
#define DEF_EPSILON   0.0000001

class bConst
{
public:
    static double get_epsilon();
    static double get_frict_f();
    static double get_spring_f();

    static void set_epsilon( double e );
    static void set_frict_f( double f );
    static void set_spring_f( double s );

protected:
    static double epsilon;
    static double friction;
    static double springness;
};

#endif // BCONST_H

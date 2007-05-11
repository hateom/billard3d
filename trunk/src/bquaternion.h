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

#ifndef BQUATERNION_H
#define BQUATERNION_H

/**
    @author Tomasz Huczek & Andrzej Jasiński <thuczek@gmail.com>
 */
class bQuaternion  
{
public:
    bQuaternion();
    bQuaternion( double x, double y, double z, double degrees);
    virtual ~bQuaternion();
    
	bQuaternion operator *( bQuaternion q );
    
	void create_matrix( double * matrix );
    void create_matrix( float * matrix );
	void create_from_axis_angle( double x, double y, double z, double degrees);

private:
	double m_w;
	double m_z;
	double m_y;
	double m_x;
};

#endif // BQUATERNION_H

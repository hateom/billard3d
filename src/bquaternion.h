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
	//bQuaternion( bQuaternion & rhs );
	bQuaternion( const bQuaternion & rhs );
    bQuaternion( double w, double x, double y, double z );
	bQuaternion( double roll, double pitch, double yaw );
    virtual ~bQuaternion();

	void from_axis( double roll, double pitch, double yaw );
	void from_matrix( double mat[16] );
	void to_matrix( double mat[16] ) const;

	bQuaternion & normalize();
	bQuaternion get_normal() const;

	bQuaternion & inverse();
	bQuaternion get_inversed() const;

	bQuaternion operator=( bQuaternion rhs );

    double length() const;
	double dot( const bQuaternion & q ) const;
    
    bQuaternion & operator +=( const bQuaternion & q );
    bQuaternion & operator -=( const bQuaternion & q );
    bQuaternion operator+( const bQuaternion & q );
    bQuaternion operator-( const bQuaternion & q );

	bQuaternion & operator *=( const bQuaternion & q );
    bQuaternion & operator /=( const bQuaternion & q );
    bQuaternion operator*( const bQuaternion & q );
    bQuaternion operator/( const bQuaternion & q );

public:
	double w;
    double x;
    double y;
	double z;
};

#endif // BQUATERNION_H

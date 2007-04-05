#define _USE_MATH_DEFINES
#include <cmath>
#include "pVector.h"

#define PI ((vtype)M_PI)

pVector::pVector( pVector & rhs )
{
	data[0] = rhs.data[0];
	data[1] = rhs.data[1];
}

pVector::pVector( vtype * d )
{
	data[0] = d[0];
	data[1] = d[1];
}

pVector::pVector( vtype x, vtype y )
{
	data[0] = x;
	data[1] = y;
}

pVector pVector::operator+( vtype v )
{
	pVector temp(*this);
	temp += v;
	return( temp );
}

pVector pVector::operator-( vtype v )
{
	pVector temp(*this);
	temp -= v;
	return( temp );
}

pVector pVector::operator*( vtype v )
{
	pVector temp(*this);
	temp *= v;
	return( temp );
}

pVector & pVector::operator+=( vtype v )
{
	data[0] += v;
	data[1] += v;
	return( *this );
}

pVector & pVector::operator-=( vtype v )
{
	data[0] -= v;
	data[1] -= v;
	return( *this );
}

pVector & pVector::operator*=( vtype v )
{
	data[0] *= v;
	data[1] *= v;
	return( *this );
}

pVector pVector::operator+( pVector vec )
{
	pVector temp(*this);
	temp += vec;
	return( temp );
}

pVector pVector::operator-( pVector vec )
{
	pVector temp(*this);
	temp -= vec;
	return( temp );
}

pVector & pVector::operator+=( pVector vec )
{
	data[0] += vec[0];
	data[1] += vec[1];
	return( *this );
}

pVector & pVector::operator-=( pVector vec )
{
	data[0] -= vec[0];
	data[1] -= vec[1];
	return( *this );
}

bool pVector::operator==( pVector & vec )
{
	return( data[0] == vec.data[0] && data[1] == vec.data[1] );
}

bool pVector::operator!=( pVector & vec )
{
	return( !operator==( vec ) );
}

pVector & pVector::operator=( pVector v )
{
	data[0] = v[0];
	data[1] = v[1];
	return( *this );
}

vtype pVector::Length()
{
	return( sqrt(data[0]*data[0] + data[1]*data[1]) );
}

void pVector::Unitize()
{
	vtype len = Length();
	if( len == 0.0f ) return;
	data[0] /= len;
	data[1] /= len;
}

pVector pVector::Unit()
{
	pVector temp(*this);
	temp.Unitize();
	return( temp );
}

vtype DotProduct( pVector & v1, pVector & v2 )
{
	return( v1[0]*v2[0] + v1[1]*v2[1] );
}

vtype CrossProduct( pVector & v1, pVector & v2 )
{
	return( v1[0]*v2[1] - v1[1]*v2[0] );
}

vtype VecAngle( pVector & v1, pVector & v2 )
{
	vtype cos, alfa;

	cos = DotProduct( v1, v2 )/(v1.Length()*v2.Length());
	alfa = acosf( cos );

	if( CrossProduct( v1, v2 ) > 0.0f )
		return( 2.0f*PI-alfa );
	else
		return( alfa );
}

vtype Distance( pVector & v1, pVector & v2 )
{
	return( sqrtf( (v2[0]-v1[0])*(v2[0]-v1[0]) + (v2[1]-v1[1])*(v2[1]-v1[1]) ) );
}

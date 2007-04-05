#ifndef __P_VECTOR_H__
#define __P_VECTOR_H__

typedef double vtype;

class pVector
{
public:
	pVector() {}
	pVector( pVector & rhs );
	pVector( vtype * d );
	pVector( vtype x, vtype y );

	pVector operator+( vtype v );
	pVector operator-( vtype v );
	pVector operator*( vtype v );

	pVector & operator+=( vtype v );
	pVector & operator-=( vtype v );
	pVector & operator*=( vtype v );

	pVector operator+( pVector vec );
	pVector operator-( pVector vec );

	pVector & operator+=( pVector vec );
	pVector & operator-=( pVector vec );

	bool operator==( pVector & vec );
	bool operator!=( pVector & vec );

	pVector & operator=( pVector v );

	vtype Length();
	void Unitize();
	pVector Unit();
    void Zero() { data[0] = data[1] = 0.0; }

	vtype & operator[]( unsigned char index ) { return( data[index] ); }

	vtype data[2];
};

vtype DotProduct( pVector & v1, pVector & v2 );
vtype CrossProduct( pVector & v1, pVector & v2 );
vtype VecAngle( pVector & v1, pVector & v2 );
vtype Distance( pVector & v1, pVector & v2 );

#endif // __P_VECTOR_H__

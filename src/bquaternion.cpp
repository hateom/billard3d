#include "bquaternion.h"
#include "bconst.h"
#include <cmath>

bQuaternion::bQuaternion()
{
    x = y = z = 0.0;
    w = 1.0;
}
/*
bQuaternion::bQuaternion( bQuaternion & rhs ) : 
	x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
{
}
*/
bQuaternion::bQuaternion( const bQuaternion & rhs ) : 
	x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
{
}

bQuaternion::bQuaternion( double iw, double ix, double iy, double iz ) : 
	x(ix), y(iy), z(iz), w(iw)
{
}

bQuaternion::bQuaternion( double roll, double pitch, double yaw )
{
	from_axis( roll, pitch, yaw );
}

bQuaternion::~bQuaternion()
{
}

bQuaternion bQuaternion::operator=( bQuaternion rhs )
{
	w = rhs.w;
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;

	return *this;
}

void bQuaternion::from_axis( double roll, double pitch, double yaw )
{
	double cr, cp, cy, sr, sp, sy, cpcy, spsy;

	cr = cos(roll/2);
	cp = cos(pitch/2);
	cy = cos(yaw/2);

	sr = sin(roll/2);
	sp = sin(pitch/2);
	sy = sin(yaw/2);
	
	cpcy = cp * cy;
	spsy = sp * sy;

	w = cr * cpcy + sr * spsy;
	x = sr * cpcy - cr * spsy;
	y = cr * sp * cy + sr * cp * sy;
	z = cr * cp * sy - sr * sp * cy;
}

void bQuaternion::from_matrix( double m[16] )
{
	double	tr, s;
	double	q[4];
	int		i, j, k;

	int nxt[3] = {1, 2, 0};

	//tr = m[0][0] + m[1][1] + m[2][2];
	tr = m[0] + m[5] + m[10];

	// check the diagonal

	if (tr > 0.0) {
		s = sqrt (tr + 1.0);
		w = s / 2.0;
		s = 0.5 / s;

//		x = (m[1][2] - m[2][1]) * s;
//		y = (m[2][0] - m[0][2]) * s;
//		z = (m[0][1] - m[1][0]) * s;

		x = (m[6] - m[9]) * s;
		y = (m[8] - m[2]) * s;
		z = (m[1] - m[4]) * s;
	} else {		
		// diagonal is negative
    
		i = 0;

//		if( m[1][1] > m[0][0] ) i = 1;
//		if( m[2][2] > m[i][i] ) i = 2;

		if( m[5] > m[0] ) i = 1;
		if( m[10] > m[i*4+i] ) i = 2;
    
		j = nxt[i];
		k = nxt[j];

		s = sqrt ((m[i*4+i] - (m[j*4+j] + m[k*4+k])) + 1.0);
      
		q[i] = s * 0.5;

		if (s != 0.0) s = 0.5 / s;

//		q[3] = (m[j][k] - m[k][j]) * s;
//		q[j] = (m[i][j] + m[j][i]) * s;
//		q[k] = (m[i][k] + m[k][i]) * s;

		q[3] = (m[j*4+k] - m[k*4+j]) * s;
		q[j] = (m[i*4+j] + m[j*4+i]) * s;
		q[k] = (m[i*4+k] + m[k*4+i]) * s;

		x = q[0];
		y = q[1];
		z = q[2];
		w = q[3];
	}
}

void bQuaternion::to_matrix( double m[16] ) const
{
	double wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	x2 = x + x; y2 = y + y; z2 = z + z;
	xx = x * x2;   xy = x * y2;   xz = x * z2;
	yy = y * y2;   yz = y * z2;   zz = z * z2;
	wx = w * x2;   wy = w * y2;   wz = w * z2;

//	m[0][0] = 1.0 - (yy + zz);
//	m[0][1] = xy - wz;
//	m[0][2] = xz + wy;
//	m[0][3] = 0.0;
 
//	m[1][0] = xy + wz;
//	m[1][1] = 1.0 - (xx + zz);
//	m[1][2] = yz - wx;
//	m[1][3] = 0.0;

//	m[2][0] = xz - wy;
//	m[2][1] = yz + wx;
//	m[2][2] = 1.0 - (xx + yy);
//	m[2][3] = 0.0;

//	m[3][0] = 0;
//	m[3][1] = 0;
//	m[3][2] = 0;
//	m[3][3] = 1;

	m[0] = 1.0 - (yy + zz);
	m[1] = xy - wz;
	m[2] = xz + wy;
	m[3] = 0.0;
 
	m[4] = xy + wz;
	m[5] = 1.0 - (xx + zz);
	m[6] = yz - wx;
	m[7] = 0.0;

	m[8] = xz - wy;
	m[9] = yz + wx;
	m[10] = 1.0 - (xx + yy);
	m[11] = 0.0;

	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

bQuaternion & bQuaternion::normalize()
{
	double	dist, square;

	square = x * x + y * y + z * z + w * w;
	
	if( square > 0.0 ) {
		dist = 1.0 / sqrt(square);
	} else { 
		dist = 1.0;
	}

    x *= dist;
    y *= dist;
    z *= dist;
    w *= dist;

	return *this;
}

bQuaternion bQuaternion::get_normal() const
{
	bQuaternion qn( *this );
	qn.normalize();
	return qn;
}

bQuaternion & bQuaternion::inverse()
{
	double norm, invNorm;

	norm = x * x + y * y + z * z + w * w;
	
	invNorm = 1.0 / norm;
	
	x = -x * invNorm;
    y = -y * invNorm;
    z = -z * invNorm;
    w =  w * invNorm;

	return *this;
}

bQuaternion bQuaternion::get_inversed() const
{
	bQuaternion qn( *this );
	qn.inverse();
	return qn;
}

bQuaternion & bQuaternion::operator +=( const bQuaternion & q )
{
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;

	normalize();

	return *this;
}

bQuaternion & bQuaternion::operator -=( const bQuaternion & q )
{
	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;

	normalize();

	return *this;
}

bQuaternion bQuaternion::operator+( const bQuaternion & q )
{
	bQuaternion qn( *this );

	qn += q;

	return qn;
}

bQuaternion bQuaternion::operator-( const bQuaternion & q )
{
	bQuaternion qn( *this );

	return qn;
}

bQuaternion & bQuaternion::operator*=( const bQuaternion & q )
{
	double ow, ox, oy, oz;

	ox = w * q.x + x * q.w + y * q.z - z * q.y;
	oy = w * q.y + y * q.w + z * q.x - x * q.z;
	oz = w * q.z + z * q.w + x * q.y - y * q.x;
	ow = w * q.w - x * q.x - y * q.y - z * q.z;

	w = ow; x = ox; y = oy; z = oz;

	normalize();

	return *this;
}

bQuaternion & bQuaternion::operator/=( const bQuaternion & iq )
{
	bQuaternion q( iq.w, -iq.x, -iq.y, -iq.z ), r(*this), s;

	r *= q;
	s = q*q;

	x = r.x / s.w;
	y = r.y / s.w;
	z = r.z / s.w;
	w = r.w / s.w;

	return *this;
}

bQuaternion bQuaternion::operator*( const bQuaternion & q )
{
	bQuaternion qn( *this );

	qn *= q;

	return qn;
}

bQuaternion bQuaternion::operator/( const bQuaternion & q )
{
	bQuaternion qn( *this );

	qn /= q;

	return qn;
}

double bQuaternion::length() const
{
	return sqrt( w * w + x * x + y * y + z * z );
}

double bQuaternion::dot( const bQuaternion & q ) const
{
	return w * q.w + x * q.x + y * q.y + z * q.z;
}

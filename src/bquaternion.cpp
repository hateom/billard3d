#include "bquaternion.h"
#include "bconst.h"
#include <cmath>

bQuaternion::bQuaternion()
{
    x = y = z = 0.0;
    w = 1.0;
}

bQuaternion::bQuaternion( bQuaternion & rhs ) : 
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

void bQuaternion::from_matrix( double mat[16] )
{
	double	tr, s;
	double	q[4];
	int		i, j, k;
	double ** m = (double**)&mat[0];

	int nxt[3] = {1, 2, 0};

	tr = m[0][0] + m[1][1] + m[2][2];

	// check the diagonal

	if (tr > 0.0) {
		s = sqrt (tr + 1.0);
		w = s / 2.0;
		s = 0.5 / s;

		x = (m[1][2] - m[2][1]) * s;
		y = (m[2][0] - m[0][2]) * s;
		z = (m[0][1] - m[1][0]) * s;
	} else {		
		// diagonal is negative
    
		i = 0;

		if( m[1][1] > m[0][0] ) i = 1;
		if( m[2][2] > m[i][i] ) i = 2;
    
		j = nxt[i];
		k = nxt[j];

		s = sqrt ((m[i][i] - (m[j][j] + m[k][k])) + 1.0);
      
		q[i] = s * 0.5;

		if (s != 0.0) s = 0.5 / s;

		q[3] = (m[j][k] - m[k][j]) * s;
		q[j] = (m[i][j] + m[j][i]) * s;
		q[k] = (m[i][k] + m[k][i]) * s;

		x = q[0];
		y = q[1];
		z = q[2];
		w = q[3];
	}
}

void bQuaternion::to_matrix( double mat[16] )
{
	double wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
	double ** m = (double**)&mat[0];

	x2 = x + x; y2 = y + y; z2 = z + z;
	xx = x * x2;   xy = x * y2;   xz = x * z2;
	yy = y * y2;   yz = y * z2;   zz = z * z2;
	wx = w * x2;   wy = w * y2;   wz = w * z2;

	m[0][0] = 1.0 - (yy + zz);
	m[0][1] = xy - wz;
	m[0][2] = xz + wy;
	m[0][3] = 0.0;
 
	m[1][0] = xy + wz;
	m[1][1] = 1.0 - (xx + zz);
	m[1][2] = yz - wx;
	m[1][3] = 0.0;

	m[2][0] = xz - wy;
	m[2][1] = yz + wx;
	m[2][2] = 1.0 - (xx + yy);
	m[2][3] = 0.0;

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

#include "bquaternion.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

bQuaternion::bQuaternion()
{
    m_x = m_y = m_z = 0.0;
    m_w = 1.0;
}


bQuaternion::bQuaternion(double x, double y, double z, double degrees)
{
    create_from_axis_angle( x, y, z, degrees );
}

bQuaternion::~bQuaternion()
{
}

void bQuaternion::create_from_axis_angle( double x, double y, double z, double degrees)
{
    double angle = double((degrees / 180.0) * M_PI);
    // Here we calculate the sin( theta / 2) once for optimization
    double result = (double)sin( angle / 2.0 );
		
    // Calcualte the w value by cos( theta / 2 )
    m_w = (double)cos( angle / 2.0 );
    // Calculate the x, y and z of the quaternion
    m_x = double(x * result);
    m_y = double(y * result);
    m_z = double(z * result);
}

void bQuaternion::create_matrix(double *pMatrix)
{
    // Make sure the matrix has allocated memory to store the rotation data
    if(!pMatrix) return;
    // First row
    pMatrix[ 0] = 1.0 - 2.0 * ( m_y * m_y + m_z * m_z ); 
    pMatrix[ 1] = 2.0 * (m_x * m_y + m_z * m_w);
    pMatrix[ 2] = 2.0 * (m_x * m_z - m_y * m_w);
    pMatrix[ 3] = 0.0;  
    // Second row
    pMatrix[ 4] = 2.0 * ( m_x * m_y - m_z * m_w );  
    pMatrix[ 5] = 1.0 - 2.0 * ( m_x * m_x + m_z * m_z ); 
    pMatrix[ 6] = 2.0 * (m_z * m_y + m_x * m_w );  
    pMatrix[ 7] = 0.0;  
    // Third row
    pMatrix[ 8] = 2.0 * ( m_x * m_z + m_y * m_w );
    pMatrix[ 9] = 2.0 * ( m_y * m_z - m_x * m_w );
    pMatrix[10] = 1.0 - 2.0 * ( m_x * m_x + m_y * m_y );  
    pMatrix[11] = 0.0;  
    // Fourth row
    pMatrix[12] = 0;  
    pMatrix[13] = 0;  
    pMatrix[14] = 0;  
    pMatrix[15] = 1.0;
    // Now pMatrix[] is a 4x4 homogeneous matrix that can be applied to an OpenGL Matrix
}

bQuaternion bQuaternion::operator *(bQuaternion q)
{
    bQuaternion r;
    r.m_w = m_w*q.m_w - m_x*q.m_x - m_y*q.m_y - m_z*q.m_z;
    r.m_x = m_w*q.m_x + m_x*q.m_w + m_y*q.m_z - m_z*q.m_y;
    r.m_y = m_w*q.m_y + m_y*q.m_w + m_z*q.m_x - m_x*q.m_z;
    r.m_z = m_w*q.m_z + m_z*q.m_w + m_x*q.m_y - m_y*q.m_x;
	
    return r;
}

void bQuaternion::create_matrix(float * pMatrix)
{
    // Make sure the matrix has allocated memory to store the rotation data
    if(!pMatrix) return;
    // First row
    pMatrix[ 0] = 1.0f - 2.0f * ( m_y * m_y + m_z * m_z ); 
    pMatrix[ 1] = 2.0f * (m_x * m_y + m_z * m_w);
    pMatrix[ 2] = 2.0f * (m_x * m_z - m_y * m_w);
    pMatrix[ 3] = 0.0f;  
    // Second row
    pMatrix[ 4] = 2.0f * ( m_x * m_y - m_z * m_w );  
    pMatrix[ 5] = 1.0f - 2.0f * ( m_x * m_x + m_z * m_z ); 
    pMatrix[ 6] = 2.0f * (m_z * m_y + m_x * m_w );  
    pMatrix[ 7] = 0.0f;  
    // Third row
    pMatrix[ 8] = 2.0f * ( m_x * m_z + m_y * m_w );
    pMatrix[ 9] = 2.0f * ( m_y * m_z - m_x * m_w );
    pMatrix[10] = 1.0f - 2.0f * ( m_x * m_x + m_y * m_y );  
    pMatrix[11] = 0.0f;  
    // Fourth row
    pMatrix[12] = 0;  
    pMatrix[13] = 0;  
    pMatrix[14] = 0;  
    pMatrix[15] = 1.0;
}

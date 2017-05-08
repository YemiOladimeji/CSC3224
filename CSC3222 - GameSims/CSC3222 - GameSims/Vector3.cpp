#include "Vector3.h"
#include <math.h>

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool Vector3::compareFloat(float a, float b, float epsilon)
{
	return (fabs(a-b) < epsilon);
}

void Vector3::inverse(float v[3]) {
	v[0] = -v[0]; //invert x
	v[1] = -v[1]; //invert y
	v[2] = -v[2]; //invert z
}

void Vector3::copy(const float v[3], float out[3])
{
	out[0] = v[0];
	out[1] = v[1];
	out[2] = v[2];
}

bool Vector3::compare(const float v0[3], const float v1[3])
{
	return (compareFloat(v0[0], v1[0]) && compareFloat(v0[1], v1[1]) && compareFloat(v0[2], v1[2]));
}

float Vector3::dist(const float p1[3], const float p2[3])
{
	float x = p1[0] - p2[0];
	float y = p1[1] - p2[1];
	float z = p1[2] - p2[2];
	return sqrt(x*x + y*y + z*z);
}

#include "Vector3.h"
#include <math.h>

//Three argument constructor
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//Function to compare floating point numbers
bool Vector3::compareFloat(float a, float b, float epsilon = 0.005f)
{
	return (fabs(a-b) < epsilon);
}

//Function to calculate the inverse of the Vector
void Vector3::inverse(float v[3]) {
	v[0] = -v[0]; //invert x
	v[1] = -v[1]; //invert y
	v[2] = -v[2]; //invert z
}

//Function to copy the values from one Vector to another
void Vector3::copy(const float v[3], float out[3])
{
	out[0] = v[0];
	out[1] = v[1];
	out[2] = v[2];
}

//Function to compare the values of two Vectors
bool Vector3::compare(const float v0[3], const float v1[3])
{
	return (compareFloat(v0[0], v1[0]) && compareFloat(v0[1], v1[1]) && compareFloat(v0[2], v1[2]));
}

//Function to calculate the distance between two Vectors
float Vector3::dist(Vector3 v1, Vector3 v2)
{
	Vector3 d = Vector3((v1.getX() - v2.getX()),(v1.getY() - v2.getY()),(v1.getZ() - v2.getZ()));
	return d.getMagnitudeSquared();
}

//Function to set the 'x' value of the vector
void Vector3::setX(float x)
{
	this->x = x;
}

//Function to set the 'y' value of the vector
void Vector3::setY(float y)
{
	this->y = y;
}

//Function to set the 'z' value of the vector
void Vector3::setZ(float z)
{
	this->z = z;
}

//Function to return the Entity's 'x' position
float Vector3::getX()
{
	return x;
}

//Function to return the Entity's 'y' position
float Vector3::getY()
{
	return y;
}

//Function to return the Entity's 'z' position
float Vector3::getZ()
{
	return z;
}

//Add vectors together
Vector3 Vector3::operator+(const Vector3 v)
{
	return Vector3((x + v.x), (y + v.y), (z+v.z));
}

//Subtract vectors from eachother
Vector3 Vector3::operator-(const Vector3 v)
{
	return Vector3((x - v.x),(y - v.y),(z - v.z));
}

//Multiply a vector by a scalar
Vector3 Vector3::operator*(const float n)
{
	return Vector3((x * n),(y * n),(z * n));
}

//Calculate the scalar product
Vector3 Vector3::operator*(const Vector3 v)
{
	return Vector3((x * v.x),(y * v.y),(z * v.z));
}

//Divide a vector by a scalar
Vector3 Vector3::operator/(const Vector3 v)
{
	return Vector3((x / v.x),(y / v.y),(z / v.z));
}

bool Vector3::operator==(const Vector3 & v)
{
	return (x == v.x && y == v.y && z == v.z);
}

//Compute the magnitude of a vector
float Vector3::getMagnitudeSquared()
{
	return x * x + y * y + z * z;
}

//Return the normalised value of a Vector
Vector3 Vector3::normalise()
{
	float mag = getMagnitudeSquared();
	x /= mag;
	y /= mag;
	z /= mag;
	return Vector3(x, y, z);
}

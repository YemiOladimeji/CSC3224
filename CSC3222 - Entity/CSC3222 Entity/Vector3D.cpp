//Author: Yemi Oladimeji
//Necessary include statements
#include <iostream>
#include <math.h>
#include "Vector3D.h" 
using namespace std;

//Default constructor
Vector3D::Vector3D() {
	setX(0);
	setY(0);
	setZ(0);
}

//Paramterised constructor
Vector3D::Vector3D(float x, float y, float z) {
	setX(x);
	setY(y);
	setZ(z);
}

//Copy constructor
Vector3D::Vector3D(const Vector3D & v) {
	x = v.getX();
	y = v.getY();
	z = v.getZ();
}

//Assignment operator
const Vector3D Vector3D::operator=(const Vector3D & v)
{
	x = v.getX();
	y = v.getY();
	z = v.getZ();
	return *this;
}

//Compute the magnitude of a vector
float Vector3D::getMagnitudeSquared() const {
	return x * x + y * y + z * z;
}

//Add vectors together
Vector3D Vector3D::operator+ (const Vector3D &v) const {
	return Vector3D(x + v.getX(), y + v.getY(), z + v.getZ());
}

//Subtract vectors from eachother
Vector3D Vector3D::operator- (const Vector3D &v) const {
	return Vector3D(x - v.getX(), y - v.getY(), z - v.getZ());
}

//Multiply a vector by a scalar
Vector3D Vector3D::operator* (float n) const {
	return Vector3D(x * n, y * n, z * n);
}

//Divide a vector by a scalar
Vector3D Vector3D::operator/ (const Vector3D &v) const {
	return Vector3D(v.getX() / x, v.getY() / y, v.getZ() / z);
}

//Calculate the scalar product
Vector3D Vector3D::operator* (const Vector3D &v) const {
	return Vector3D(v.getX()*x, v.getY()*y, v.getZ()*z);
}

//Calculate the vector product
Vector3D Vector3D::operator% (const Vector3D &v) const {
	return Vector3D(y*v.getZ() - z*v.getY(),
		z*v.getX() - x*v.getZ(),
		x*v.getY() - y*v.getX());
}

bool Vector3D::operator==(const Vector3D & v) const
{
	return (x == v.x && y == v.y && z == v.z);
}

bool Vector3D::operator!=(const Vector3D & v) const
{
	return !(x == v.x && y == v.y && z == v.z);
}

//Create a unit vector
Vector3D Vector3D::normaliseVector3D() {
	float mag = getMagnitudeSquared();
	x /= mag;
	y /= mag;
	z /= mag;
	return Vector3D(x, y, z);
}


float Vector3D::vectorDistance(const Vector3D &v)
{
	Vector3D t = Vector3D(x - v.getX(), y - v.getY(), z - v.getZ());
	return t.getMagnitudeSquared();
}

ostream &operator<<(ostream &outStream, const Vector3D &v)
{
	outStream << "(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
	return outStream;
}
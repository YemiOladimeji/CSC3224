#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

using namespace std;

class Vector3 {

public:
	Vector3(float x, float y, float z);	//Three argument constructor
	virtual ~Vector3() {}; //Destructor

	float x, y, z; 	//Indivdual position components for the Vector
	bool compareFloat(float a, float b, float epsilon); //Function to compare floating point numbers

	void inverse(float v[3]); //Function to calculate the inverse of the Vector
	void copy(const float v[3], float out[3]); //Function to copy the values from one Vector to another
	bool compare(const float v0[3], const float v1[3]); //Function to compare the values of two Vectors
	float dist(Vector3 v1, Vector3 v2); //Function to calculate the distance between two Vectors

	//Overload functions
	Vector3 operator+ (const float v[3]); //Add vectors together
	Vector3 operator- (const float v[3]); //Subtract vectors from eachother
	Vector3 operator* (const float n); //Multiply a vector by a scalar
	Vector3 operator* (const float v[3]); //Calculate the scalar product
	Vector3 operator/ (const float v[3]); //Divide a vector by a scalar
	bool operator== (const Vector3 &v); //Compare to see if two Vectors are equal to each other

	float getX(); //Function to return the Entity's 'x' position
	float getY(); //Function to return the Entity's 'y' position
	float getZ(); //Function to return the Entity's 'z' position

	//Calculate the magnitude of a Vector
	float getMagnitudeSquared();
};
#endif VECTOR3_H

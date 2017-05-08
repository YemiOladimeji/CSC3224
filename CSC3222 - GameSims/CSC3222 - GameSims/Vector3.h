#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

using namespace std;

class Vector3 {

protected:
	//Indivdual position components for the Vector
	float x, y, z;

public:
	Vector3(float x, float y, float z);	//Three argument constructor
	virtual ~Vector3() {}; //Destructor

	bool compareFloat(float a, float b, float epsilon = 0.005f); //Function to compare floating point numbers

	void inverse(float v[3]); //Function to calculate the inverse of the Vector
	void copy(const float v[3], float out[3]); //Function to copy the values from one Vector to another
	bool compare(const float v0[3], const float v1[3]); //Function to compare the values of two Vectors
	float dist(const float p1[3], const float p2[3]); //Function to calculate the distance between two Vectors
};
#endif VECTOR3_H

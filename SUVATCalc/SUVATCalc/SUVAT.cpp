#pragma once
#include "SUVAT.h"
#include "Vector3D.h"
#include <iostream>

using namespace std;

SUVAT::SUVAT(){ //Default constructor

}

inline void SUVAT::setTime(float t){
	this->t = t;
}

inline float SUVAT::getTime()
{
	return t;
}

Vector3D SUVAT::calculate(Vector3D u, Vector3D a, float t){
	Vector3D v = u + (a * t);
	return v;
}



#include "..\..\CSC3222 - GameSims\CSC3222 - GameSims\SUVAT.h"

#pragma once
#include "SUVAT.h"
#include "Vector3D.h"
#include <iostream>

using namespace std;

SUVAT::SUVAT(){ //Default constructor

}


Vector3 SUVAT::calculate(Vector3 u, Vector3 v, float t)
{
	return Vector3();
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



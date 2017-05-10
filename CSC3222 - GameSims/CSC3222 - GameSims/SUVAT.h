#pragma once
#ifndef SUVAT_H
#define SUVAT_H

#include "Vector3.h"

class SUVAT
{

public:
	SUVAT(); //Default constructor
	virtual ~SUVAT() {}; //Destructor

	static float getV(float u, float a, float t);
	static float getS(float u, float a, float t);
	static float getSFromUAT(float u, float v, float t);
	static float getVFromUAS(float u, float a, float s);
	static float getSFromVTA(float v, float t, float a);

	static Vector3 getV(Vector3 &u, Vector3 a, Vector3 &t);
	static Vector3 getS(Vector3 &u, Vector3 &a, Vector3 &t);
	static Vector3 getSFromUVT(Vector3 &u, Vector3 &v, Vector3 &t);
	static Vector3 getVFromUAS(Vector3 &u, Vector3 &a, Vector3 &s);
	static Vector3 getSFromVTA(Vector3 &v, Vector3 &t, Vector3 &a);
};

#endif SUVAT_H

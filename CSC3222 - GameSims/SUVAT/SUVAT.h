#pragma once
#ifndef SUVAT_H
#define SUVAT_H

#include "Vector3.h"

class SUVAT 
{
	
private:
	Vector3 u, a;
	float t;

public:
	SUVAT(); //Default constructor
	virtual ~SUVAT() {}; //Destructor

	inline void setTime(float time) {
		this->t = time;
	}

	inline float getTime() {
		return t;
	}

	Vector3 calculate(Vector3 u, Vector3 a, float t);
};

#endif SUVAT_H

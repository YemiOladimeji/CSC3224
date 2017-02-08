#pragma once
#include "Vector3D.h"
#ifndef SUVAT_H
#define SUVAT_H


class SUVAT {

private:
	Vector3D u;
	Vector3D a;
	float t;

public:
	//Constructors
	SUVAT(); //Default constructor
	~SUVAT() {}; //Destructor 
	
	SUVAT(const SUVAT &s); //Copy constructor
	const SUVAT	operator= (const SUVAT &s); //Assignment operator

	inline void setTime();
	inline float getTime();
};
#endif //SUVAT_H

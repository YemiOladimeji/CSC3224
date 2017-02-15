#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include "Vector3D.h"

using namespace std;

class Entity {

private:
	typedef struct{ //Struct to hold the position of the Entity
		float x;
		float y;
		float z;

		float getX() {
			return x;
		}

		float getY() {
			return y;
		}

		float getZ() {
			return z;
		}

		float getMagnitude() {
			return sqrtf(x*x + y*y + z*z);
		}
	}Vector3;

	float aggroRange;
	int entitiesInRange;

public:
	Entity(); //Default constructor
	Entity(Vector3 pos, float aR); //Parameterised constructor
	~Entity() {}; //Destructor
	Entity(const Entity &e); //Copy constructor
	Entity operator= (const Entity &e); //Assignment operator

	//Get functions
	float getAggroRange();
	int getEntitiesInRange();
	float getDistanceBetween();

	//Update functions
	void updatePosition(Vector3 position);
	void updateAggroRange();
	void updateEntitiesInRange(int entitiesInRange);
};
ostream &operator<< (ostream &outStream, Entity &e); //Output operator
#endif
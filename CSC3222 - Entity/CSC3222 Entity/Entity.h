#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include "Vector3D.h"

using namespace std;

class Entity {

private:
	float aggroRange;
	int entitiesInRange;

public:
	Entity(); //Default constructor
	Entity(Vector3D pos, float aR); //Parameterised constructor
	~Entity() {}; //Destructor
	Entity(const Entity &e); //Copy constructor
	Entity operator= (const Entity &e); //Assignment operator

	//Get functions
	float getAggroRange();
	int getEntitiesInRange();

	//Update functions
	void updatePosition(Vector3D position);
	void updateAggroRange(float x);
	void updateEntitiesInRange(int entitiesInRange);
};
ostream &operator<< (ostream &outStream, Entity &e); //Output operator
#endif
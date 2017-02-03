#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>

using namespace std;

class Entity {

private:
	struct Vector3 {
		float x;
		float y;
		float z;
	};

	float aggroRange;
	int entitiesInRange;

public:
	Entity(Vector3 pos, float aR); //Default constructor
	~Entity() {}; //Destructor
	Entity(Entity &e); //Copy constructor
	Entity operator= (Entity &e); //Assignment operator

	//Get functions
	float getAggroRange();
	int getEntitiesInRange();

	//Update functions
	void updatePosition(Vector3 position);
	void updateAggroRange();
	void updateEntitiesInRange(int entitiesInRange);
};
#endif
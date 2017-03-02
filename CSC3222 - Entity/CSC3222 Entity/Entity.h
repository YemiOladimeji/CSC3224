#pragma once
#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <vector>
#include "Vector3D.h"

using namespace std;

class Entity {

private:
	float aggroRange;
	int entitiesInRange;
	Vector3D position;

public:
	Entity(); //Default constructor
	Entity(Vector3D pos, float aR); //Parameterised constructor
	~Entity() {}; //Destructor
	Entity(const Entity &e); //Copy constructor
	Entity operator= (const Entity &e); //Assignment operator
	bool operator== (const Entity &e);
	bool operator!= (const Entity &e);
				
	
	//Get functions
	float getAggroRange();
	int getEntitiesInRange();
	Vector3D getPosition();
	float getEntityX();
	float getEntityY();
	float getEntityZ();

	//Update functions
	void updatePosition(Vector3D position);
	void updateAggroRange(float x);
	void updateEntitiesInRange(vector<Entity> v);
};
#endif
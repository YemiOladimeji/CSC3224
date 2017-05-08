#pragma once
#ifndef ENTITY_H
#define ENTITY_H

//Include the Vector3 class
#include "Vector3.h"
#include <vector>

class Entity {

private:
	Vector3 position; //Instantiate a Vector3 object
	float aggroRange; //Declare a floating point field called aggroRange
	int entitiesInRange; //Declare an integer field called entitiesInRange

public:
	void updateX(Vector3 pos); //Function to update the 'x' component of the position vector
	void updateY(Vector3 pos); //Function to update the 'y' component of the position vector
	void updateZ(Vector3 pos); //Function to update the 'z' component of the position vector
	void updatePosition(Vector3 pos); //Function to update the position vector as a whole

	void updateAggroRange(float x); //Function to update the aggroRange variable
	void updateEntitiesInRange(vector<Entity> v); //Function to update the entitiesInRange variable

	Vector3 getPosition(); //Function to return the current position of the Entity
	float getAggroRange(); //Function to return the aggroRange variable
	int getEntitiesInRange(); //Function to return the entitiesInRange variable

	bool operator== (const Entity &e); //Equality overload function
};
#endif ENTITY_H

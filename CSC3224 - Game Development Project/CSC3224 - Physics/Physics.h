#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include "Box2D\Box2D.h"

using namespace std;

class Physics {

public:

	Physics(); //Default constructor
	~Physics() {}; //Destructor

	void createPlayerBody(b2World& world, float x, float y, float scale, float radius); //Function for setting a player body
	void createEnemyBody(b2World & world, float x, float y, float scale, float radius); //Function for setting an enemy
	void createGround(b2World& world, float x, float y, float scale, float height, float width); //Function for setting a default ground platform
};

#endif //PHYSICS_H

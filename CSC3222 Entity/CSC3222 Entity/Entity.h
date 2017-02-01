#pragma once
#include <iostream>

using namespace std;

class Entity {

private:
	struct Position {
		float x;
		float y;
		float z;
	};

	float aggroRange;
	int entitiesInRange;

public:
	Entity(Position pos, float aR) { //Default constructor
		
	}

	//Get functions
	float getAggroRange();
	int getEntitiesInRange();

	//Update functions
	void updatePosition(Position position);
	void updateAggroRange();
	void updateEntitiesInRange(int entitiesInRange);
};
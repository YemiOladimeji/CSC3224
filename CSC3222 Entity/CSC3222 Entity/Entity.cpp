#include <iostream>
#include "Entity.h"
using namespace std;

Entity::Entity() { //Default constructor

}

Entity::Entity(Vector3 pos, float aR){ //Parameterised constructor
	pos = {0,0,0};
	aR = 0.0;
}

Entity::Entity(const Entity & e){ //Copy constructor
	
}

Entity Entity::operator=(const Entity & e){ //Assignment operator
	return Entity();
}

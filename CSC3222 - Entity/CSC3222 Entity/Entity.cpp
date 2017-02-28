#include <iostream>
#include "Entity.h"
using namespace std;

Entity::Entity() { //Default constructor

}

Entity::Entity(Vector3D pos, float aR)
{
}

Entity::Entity(Vector3D pos, float aR){ //Parameterised constructor
	pos = {0,0,0};
	aR = 0.0;
}

Entity::Entity(const Entity & e){ //Copy constructor
	
}

Entity Entity::operator=(const Entity & e){ //Assignment operator
	return Entity();
}

float Entity::getAggroRange()
{
	return aggroRange;
}

int Entity::getEntitiesInRange()
{
	return entitiesInRange;
}

void Entity::updatePosition(Vector3D position)
{
}

void Entity::updateAggroRange(float x)
{
	aggroRange = x;
}

void Entity::updateEntitiesInRange(int entitiesInRange)
{
}

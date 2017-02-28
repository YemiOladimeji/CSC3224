#include <iostream>
#include "Entity.h"
using namespace std;

Entity::Entity() { //Default constructor

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

void Entity::updatePosition(Vector3D pos)
{
	position.setX(pos.getX());
	position.setY(pos.getY());
	position.setZ(pos.getZ());
}

void Entity::updateAggroRange(float x)
{
	aggroRange = x;
}

void Entity::updateEntitiesInRange(Vector3D vec)//array of entities here
{
	if (aggroRange < vectorDistance(vec)) { //loop through array
											//check current position against other entities in the list/array (if entity =  this)
		                                    //get distance between this entity and the current entity in the list
		                                    //if distance between this entity and that entity is less than the aggro range of the entity the function is being called on
		                                    //update entities in range
		entitiesInRange++;
	}
}

float Entity::vectorDistance(const Vector3D &v)
{
	Vector3D t = Vector3D(position.getX() - v.getX(), position.getY() - v.getY(), position.getZ() - v.getZ());
	return t.getMagnitudeSquared();
}

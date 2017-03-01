#include <iostream>
#include <vector>
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

bool Entity::operator==(const Entity & e)
{
	return (aggroRange == e.aggroRange && entitiesInRange == e.entitiesInRange && position == e.position);
}

bool Entity::operator!=(const Entity & e)
{
	return !(aggroRange == e.aggroRange && entitiesInRange == e.entitiesInRange && position == e.position);
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

void Entity::updateEntitiesInRange(vector<Entity> v)//vector of entities here
{
	for (int x = 0; x < v.size; x++) { //loop through vector of entities
		if (v[x] == *this) { //check current position against other entities in the list/array (if entity =  this)
			entitiesInRange--;
		}
		else {
			float dist = position.vectorDistance(v[x].position); //get distance between this entity and the current entity in the list
			if (dist < aggroRange) {  //if distance between this entity and that entity is less than the aggro range of the entity the function is being called on
				entitiesInRange++; //update entities in range	
			}
		}
	}											
}

#include "Entity.h"

//Function to update the 'x' component of the position vector
void Entity::updateX(Vector3 pos)
{
	position.x = pos.getX();
}

//Function to update the 'y' component of the position vector
void Entity::updateY(Vector3 pos)
{
	position.y = pos.getY();
}

//Function to update the 'z' component of the position vector
void Entity::updateZ(Vector3 pos)
{
	position.z = pos.getZ();
}

//Function to update the position vector as a whole
void Entity::updatePosition(Vector3 pos)
{
	position.x = pos.getX();
	position.y = pos.getY();
	position.z = pos.getZ();
}

//Function to update the aggroRange variable
void Entity::updateAggroRange(float x)
{
	aggroRange = x;
}

//Function to update the entitiesInRange variable
void Entity::updateEntitiesInRange(vector<Entity> v)
{
	for (vector<Entity>::size_type x = 0; x != v.size(); x++)
	{
		if (v[x] == *this) 
		{
			entitiesInRange--;
		}
		else if(position.dist(this->getPosition(), v[x].getPosition()) < aggroRange)
		{
			entitiesInRange++;
		}
	}
}

//Function to return the current position of the Entity
Vector3 Entity::getPosition()
{
	return Vector3(position.getX(), position.getY(), position.getZ());
}

//Function to return the aggroRange variable
float Entity::getAggroRange()
{
	return aggroRange;
}

//Function to return the entitiesInRange variable
int Entity::getEntitiesInRange()
{
	return entitiesInRange;
}

//Equality overload function
bool Entity::operator==(const Entity & e)
{
	return (aggroRange == e.aggroRange && entitiesInRange == e.entitiesInRange && position == e.position);
}

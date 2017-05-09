#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;


class Collider
{
public:
	Collider(); //Default constructor
	virtual ~Collider() {}; //Destructor

	bool checkCCCollision(sf::CircleShape c1, sf::CircleShape c2); //Function to check circle-circle collision
	bool checkCRCollision(sf::CircleShape c1, sf::RectangleShape r1); //Function to check circle-rectangle collision

private:
	bool collision; //Boolean variable to check if a collision has occurred
};

#endif // !COLLIDER_H

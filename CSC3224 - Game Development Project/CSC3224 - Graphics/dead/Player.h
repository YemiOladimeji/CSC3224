#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SFML\Graphics.hpp"
#include <HumanInterface.h>

using namespace std;

class Player
{
public:

	Player(float radius, float speed); //Default constructor
	virtual ~Player() {}; //Destructor

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);

private:
	sf::CircleShape body;
	HumanInterface control;
	float speed;
};

#endif // !PLAYER_H

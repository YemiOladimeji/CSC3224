#pragma once
#ifndef HUMANINTERFACE_H
#define HUMANINTERFACE_H

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

using namespace std;

class HumanInterface {

public:
	HumanInterface(); //Default constructor for instatiating this class
	~HumanInterface() {}; //Destructor
	void moveSprite(sf::Sprite sprite, float xspeed, float yspeed);
	void moveCircle(sf::CircleShape shape, float xspeed, float yspeed);

};
#endif //HUMANINTERFACE_H

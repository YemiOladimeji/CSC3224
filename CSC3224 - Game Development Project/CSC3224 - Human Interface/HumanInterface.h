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
	sf::Sprite moveSprite(sf::Sprite sprite, float xspeed, float yspeed);
	sf::CircleShape moveCircle(sf::CircleShape shape, float xspeed, float yspeed);

};
#endif //HUMANINTERFACE_H

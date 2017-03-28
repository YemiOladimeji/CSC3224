#pragma once
#ifndef HUMANINTERFACE_H
#define HUMANINTERFACE_H

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

using namespace std;

class HumanInterface {

private:
	bool moveUp, moveDown, moveLeft, moveRight;

public:
	HumanInterface(); //Default constructor for instatiating this class
	~HumanInterface() {}; //Destructor
	bool movingUp(bool isPressed);
	bool movingDown(bool isPressed);
	bool movingLeft(bool isPressed);
	bool movingRight(bool isPressed);
	void handleInput(sf::Keyboard::Key, bool isPressed);
};
#endif //HUMANINTERFACE_H

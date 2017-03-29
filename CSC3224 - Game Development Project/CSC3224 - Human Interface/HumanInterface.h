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
	bool moveUp, moveDown, moveLeft, moveRight; //Boolean variables to detect what direction the player is moving in
	void handleInput(sf::Keyboard::Key, bool isPressed); //Function to handle key input from the player
};
#endif //HUMANINTERFACE_H

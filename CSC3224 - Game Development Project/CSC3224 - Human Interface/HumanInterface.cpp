#include "HumanInterface.h"

HumanInterface::HumanInterface()
{
	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;
	jumping = false;
}

void HumanInterface::handleInput(sf::Keyboard::Key key, bool isPressed) //Function to handle movement inputs from the player
{
	if (key == sf::Keyboard::W) {
		jumping = true;
		moveUp = isPressed;
	}
	else if(key == sf::Keyboard::A){
		moveLeft = isPressed;
	}
	else if (key == sf::Keyboard::S){
		moveDown = isPressed;
	}
	else if (key == sf::Keyboard::D) {
		moveRight = isPressed;
	}
}


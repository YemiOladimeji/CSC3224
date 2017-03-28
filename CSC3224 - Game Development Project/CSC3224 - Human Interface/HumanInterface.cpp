#include "HumanInterface.h"

HumanInterface::HumanInterface()
{
	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;
}

bool HumanInterface::movingUp(bool isPressed)
{
	moveUp = isPressed;
	return moveUp;
}

bool HumanInterface::movingDown(bool isPressed)
{
	moveDown = isPressed;
	return moveDown;
}

bool HumanInterface::movingLeft(bool isPressed)
{
	moveLeft = isPressed;
	return moveLeft;
}

bool HumanInterface::movingRight(bool isPressed)
{
	moveRight = isPressed;
	return moveRight;
}

void HumanInterface::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W) {
		movingUp(isPressed);
	}
	else if(key == sf::Keyboard::A){
		movingLeft(isPressed);
	}
	else if (key == sf::Keyboard::S){
		movingDown(isPressed);
	}
	else if (key == sf::Keyboard::D) {
		movingRight(isPressed);
	}
}

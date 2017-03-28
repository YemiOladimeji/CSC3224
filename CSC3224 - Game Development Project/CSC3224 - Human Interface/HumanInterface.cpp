#include "HumanInterface.h"

HumanInterface::HumanInterface()
{
	moveDown = false;
	moveLeft = false;
	moveRight = false;
	moveRight = false;
}

bool HumanInterface::movingUp(bool isPressed)
{
	moveUp == isPressed;
	return moveUp;
}

bool HumanInterface::movingDown(bool isPressed)
{
	return false;
}

bool HumanInterface::movingLeft(bool isPressed)
{
	return false;
}

bool HumanInterface::movingRight(bool isPressed)
{
	return false;
}

void HumanInterface::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W) {
		movingUp(isPressed);
	}
	else if(key == sf::Keyboard::A){
		moveLeft = isPressed;
	}
	else if (key == sf::Keyboard::S){
		moveDown = isPressed;
	}
	else if (key == sf::Keyboard::D) {
		moveRight == isPressed;
	}
}

#include "HumanInterface.h"

HumanInterface::HumanInterface()
{
	moveUp = false;
	moveDown = false;
	moveLeft = false;
	moveRight = false;
}

void HumanInterface::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
		moveUp = isPressed;
	}
	else if(key == sf::Keyboard::A || key == sf::Keyboard::Left){
		moveLeft = isPressed;
	}
	else if (key == sf::Keyboard::S || key == sf::Keyboard::Down){
		moveDown = isPressed;
	}
	else if (key == sf::Keyboard::D || key == sf::Keyboard::Right) {
		moveRight = isPressed;
	}
}

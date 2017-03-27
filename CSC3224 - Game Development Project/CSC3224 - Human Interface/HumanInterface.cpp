#include "HumanInterface.h"

HumanInterface::HumanInterface()
{
}

sf::CircleShape HumanInterface::moveCircle(sf::CircleShape shape, float xspeed, float yspeed) { //Function to move a circle via WASD controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		shape.move(-xspeed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		shape.move(xspeed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		shape.move(0, -yspeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		shape.move(0, yspeed);
	}
	return shape;
}

sf::Sprite HumanInterface::moveSprite(sf::Sprite sprite, float xspeed, float yspeed) { //Function to move a sprite via WASD controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sprite.move(-xspeed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sprite.move(xspeed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		sprite.move(0, -yspeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		sprite.move(0, yspeed);
	}
	return sprite;
}


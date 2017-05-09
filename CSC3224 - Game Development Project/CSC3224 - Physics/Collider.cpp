#include "Collider.h"

Collider::Collider()
{

}

bool Collider::checkCCCollision(sf::CircleShape c1, sf::CircleShape c2) 
{
	sf::FloatRect bb1 = c1.getGlobalBounds();
	sf::FloatRect bb2 = c2.getGlobalBounds();

	if (bb1.intersects(bb2)) {
		cout << "Collision!";
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool Collider::checkCRCollision(sf::CircleShape c1, sf::RectangleShape r1) 
{
	sf::FloatRect bb1 = c1.getGlobalBounds();
	sf::FloatRect bb2 = r1.getGlobalBounds();

	if (bb1.intersects(bb2)) {
		cout << "Collision!";
		return true;
	}
	else {
		return false;
	}
	return false;
}

#include "Player.h"

Player::Player(float radius, float speed) 
{
	this->speed = speed;
	this->body.setRadius(radius);
	this->body.setPosition(360.0f, 240.0f);
}

void Player::update(float deltaTime)
{
	sf::Vector2f velocity(0, 0);
	float speed = 25000;
	float rotation = 700;

	if (control.moveUp)
	{

	}
	if (control.moveLeft)
	{
		velocity.x -= speed * deltaTime;
		body.rotate(-rotation * deltaTime);
	}
	if (control.moveRight)
	{
		velocity.x += speed * deltaTime;
		body.rotate(rotation * deltaTime);
	}
	body.move(velocity);
}

void Player::draw(sf::RenderWindow &window)
{
	window.draw(body);
}

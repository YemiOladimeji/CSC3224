#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\Graphics.hpp>
using namespace std;

class Entity 
{
public:
	Entity(); //Default constructor
	virtual ~Entity() {}; //Destructor

	void createRectangle(const string &name, const sf::RectangleShape &rect, const int &radius); //Function to create an rectangle
	void createCircle(const string &name, const sf::CircleShape &circle, const sf::Vector2f &size); //Function to create an rectangle
	Entity &getEntityRef(const string& entity); //Function to fetch a reference to the specified entity

private:
	sf::RectangleShape rect; //SFML rectangle object	
	sf::CircleShape circle; //SFML circle object
	map<string, Entity>entities; //Map of created entities
};

#endif // !ENTITY_H

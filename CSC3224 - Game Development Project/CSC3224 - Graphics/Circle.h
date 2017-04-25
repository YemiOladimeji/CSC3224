#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML\Graphics.hpp>
using namespace std;

class Circle
{
public:
	Circle(); //Default constructor
	virtual ~Circle() {}; //Destructor

	void createCircle(const string &name, const float &radius); //Function to create an rectangle
	void clipCircleTex(const sf::IntRect &clip); //Function to clip a texture applied to a circle
	sf::CircleShape &getCircleRef(const string &circle); //Function to fetch the reference to the specified circle 

private:
	sf::CircleShape circle; //SFML circle object
	map<string, sf::CircleShape> circles; //Map to hold circle objects
};

#endif // !CIRCLE_H

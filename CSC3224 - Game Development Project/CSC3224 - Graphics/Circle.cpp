#include "Circle.h"
#include <iostream>

Circle::Circle() //Default constructor
{

}

void Circle::createCircle(const string &name, const float &radius) //Function to create the circle
{
	if (radius < 0) { //Condition to check whether the value of the radius is valid
		cout << "Error: Invalid radius value."; //Output error 
	}
	else {
		circle.setRadius(radius); //Set the radius of the circle with the specified value
		this->circles[name] = circle; //Add the circle to the map
		return;
	}
	return;
}

void Circle::clipCircleTex(const sf::IntRect &clip) //Function to clip the texture applied to a circle
{
	circle.setTextureRect(clip); //Clip the texture to the specified size
	return;
}

sf::CircleShape &Circle::getCircleRef(const string &circle) //Function to get a reference to the circle whose name matches the parameter
{
	return this->circles.at(circle); //Return a reference to the circle with the matching name
}
#include "Rectangle.h"

Rectangle::Rectangle() //Default constructor
{

}

void Rectangle::createRectangle(const string &name, const sf::Vector2f &size) //Function to create a rectangle
{
	if (size.x < 0 || size.y < 0) { //Condition to check that the dimensions specified are valid
		cout << "Error: Invalid size specifications."; //Output error message
	}
	else {
		rect.setSize(size); //Set the size of the rectangle
		this->rectangles[name] = rect; //Add the rectangle to the map
		return;
	}
	return;
}

sf::RectangleShape &Rectangle::getRectRef(const string &rect) //Function to fetch the reference to the rectangle with the matching name
{
	return this->rectangles.at(rect); //Return a reference to the rectangle with the matching name
}
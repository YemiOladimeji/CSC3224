#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;

class Rectangle 
{
public:
	Rectangle(); //Default constructor
	virtual ~Rectangle() {}; //Destructor

	void createRectangle(const string &name, const sf::Vector2f &size); //Function to create an rectangle
	sf::RectangleShape &getRectRef(const string& rectangle); //Function to fetch a reference to the specified entity

private:
	sf::RectangleShape rect; //SFML rectangle object
	map<string, sf::RectangleShape> rectangles; //Map of created entities
};

#endif // !RECTANGLE_H

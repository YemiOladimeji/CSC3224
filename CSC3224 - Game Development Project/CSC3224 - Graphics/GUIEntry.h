#pragma once
#ifndef GUIENTRY_H
#define GUIENTRY_H

#include<SFML\Graphics.hpp>

#include <vector>
#include <utility>
#include <string>

using namespace std;

class GUIEntry 
{
public:

	GUIEntry(); //Default constructor
	GUIEntry(const string &message, sf::RectangleShape shape, sf::Text text); //Parameterised constructor

	sf::RectangleShape shape;
	string message;
	sf::Text text;
};

#endif // !GUIENTRY_H

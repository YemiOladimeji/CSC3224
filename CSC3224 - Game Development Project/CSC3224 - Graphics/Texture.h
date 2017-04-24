#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML\Graphics.hpp> //Import the SFML Graphics module

using namespace std;

class Texture
{
public:
	Texture(); //Default constructor
	virtual ~Texture(); //Destructor

	void setName(string &name); //Function to set the name of the texture
	string getName(); //Function to retrieve the name of the texture
	sf::Texture loadTexture(const string &filepath); //Function to load an image from a file to use as a texture

private:
	string name; //Name of the texture
	sf::Texture texture; //SFML texture
};

#endif // !TEXTURE_H

#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML\Graphics.hpp>

using namespace std;

class Texture
{
public:
	Texture(string &name); //Default constructor
	virtual ~Texture(); //Destructor
	sf::Texture loadTexture(string &filepath); //Function to load an image from a file to use as a texture
	void setName(string name); //Function 
	string getName();

private:
	sf::Texture texture; //SFML texture
	string name; //Name of the texture
};

#endif // !TEXTURE_H

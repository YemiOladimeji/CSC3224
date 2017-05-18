#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML\Graphics.hpp> //Import the SFML Graphics module

using namespace std;

class Texture
{
public:
	Texture(); //Default constructor
	virtual ~Texture() {}; //Destructor

	void loadTexture(const string &name, const string &filepath); //Function to load an image from a file to use as a texture
	sf::Texture &getTexRef(const string &texture); //Function to fetch a reference to the specified texture

private:
	sf::Texture texture; //SFML texture object
	
	
	map<string, sf::Texture> textures; //Map of created texture objects
};

#endif // !TEXTURE_H

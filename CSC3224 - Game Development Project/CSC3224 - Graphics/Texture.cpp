#include "Texture.h"
#include <iostream>

Texture::Texture() //Default constructor
{
	
}

void Texture::loadTexture(const string &name, const string &filepath)  //Function to load an image and set it as a texture
{
	if (!texture.loadFromFile(filepath)) {
		cout << "Error: Unable to load texture from file."; //Output an error message when the file fails to load
	}
	else {
		texture.loadFromFile(filepath); //Load image from file into texture object
		this->textures[name] = texture; //Add the texture object to the map
		return;
	}
	return;
}

sf::Texture &Texture::getTexRef(const string &texture) 
{
	return this->textures.at(texture); //Return a reference the texture with the matching name
}
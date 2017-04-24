#include "Texture.h"

using namespace std;

Texture::Texture() //Default constructor
{
	
}

Texture::~Texture() //Function to unload the specified resource
{
}

void Texture::setName(string &name) { //Function to assign a name to the texture
	this->name = name;
}

string Texture::getName() { //Function to retrieve the name of the texture
	return name;
}

sf::Texture Texture::loadTexture(const string &filepath)  //Function to load an image and set it as a texture
{
	if (!texture.loadFromFile(filepath)) {
		
	}
	else {
		texture.loadFromFile(filepath); //Load image from file into texture object
		return texture; //Return the texture object as a loaded texture
	}
	return texture; //Return empty texture
}
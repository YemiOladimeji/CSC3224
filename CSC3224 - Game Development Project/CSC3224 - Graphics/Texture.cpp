#include "Texture.h"

using namespace std;

Texture::Texture(string &name) 
{
	setName(name); //Set the name of the texture for reference
}

Texture::~Texture() //Function to unload the specified resource
{
}

sf::Texture Texture::loadTexture(string &filepath)
{
	if (!texture.loadFromFile(filepath)) {
		
	}
	else {
		texture.loadFromFile(filepath); //Load image from file into texture object
		return texture;
	}
	return texture; //Return empty texture
}

string Texture::getName() {
	return name;
}

void Texture::setName(string name) {
	this->name = name;
}
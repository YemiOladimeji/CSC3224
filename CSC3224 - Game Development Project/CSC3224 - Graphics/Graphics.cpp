#include "Graphics.h"

Graphics::Graphics() { //Default constructor

}

sf::Sprite Graphics::loadTexture(string filepath) {
	if (!texture.loadFromFile(filepath)) { //Try and load texture from file
		cout << "Unable to load texture from file."; //Output error message
	}
	else {
		texture.loadFromFile(filepath); //Load texture
		sprite.setTexture(texture); //Apply texture to sprite
		return sprite; //Return sprite for drawing
	}
	return sprite; //Return empty sprite
}
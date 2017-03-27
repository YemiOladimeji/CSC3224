#include "Graphics.h"

Graphics::Graphics() { //Default constructor

}

sf::Sprite Graphics::textureSprite(string filepath) {
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

sf::CircleShape Graphics::textureCircle(string filepath)
{
	if (!texture.loadFromFile(filepath)) { //Try and load texture from designated filepath
		cout << "Unable to load texture from file."; //If it fails, display error message
	}
	else {
		texture.loadFromFile(filepath); //Load texture
		circle.setTexture(&texture); //Apply texture to circle
		circle.getTextureRect(sf::IntRect(10,10,500,500));
		return circle; //Return circle for drawing
	}
	return circle; //Return empty circle
}

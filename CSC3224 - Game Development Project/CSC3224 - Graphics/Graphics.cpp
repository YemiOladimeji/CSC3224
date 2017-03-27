#include "Graphics.h"

Graphics::Graphics() { //Default constructor

}

sf::Sprite Graphics::textureSprite(string filepath) 
{
	if (!texture.loadFromFile(filepath)) { //Try and load texture from file
		cout << "Unable to load texture from file."; //Output error message
	}
	else {
		texture.loadFromFile(filepath); //Load texture
		sprite.setTexture(texture); //Apply texture to sprite
		return sprite; //Return textured sprite for drawing
	}
	return sprite; //Return empty sprite
}

sf::CircleShape Graphics::textureCircle(string filepath, int radius)
{
	if (!texture.loadFromFile(filepath)) { //Try and load texture from designated filepath
		cout << "Unable to load texture from file."; //If it fails, display error message
	}
	else {
		texture.loadFromFile(filepath); //Load texture
		circle.setRadius(radius);
		circle.setTexture(&texture); //Apply texture to circle
		circle.setTextureRect(sf::IntRect(0,0,500,500));
		return circle; //Return textured circle for drawing
	}
	return circle; //Return empty circle
}

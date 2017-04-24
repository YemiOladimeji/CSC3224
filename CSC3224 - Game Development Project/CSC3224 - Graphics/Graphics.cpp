#include "Graphics.h"

Graphics::Graphics() { //Default constructor

}

sf::CircleShape Graphics::textureCircle(string filepath, int radius)
{
	if (!texture.loadFromFile(filepath)) { //Try and load texture from designated filepath
		cout << "Unable to load texture from file."; //If it fails, display error message
	}
	else {
		texture.loadFromFile(filepath); //Load texture
		circle.setRadius(radius); //Set radius to specified number
		circle.setTexture(&texture); //Apply texture to circle
		circle.setTextureRect(sf::IntRect(0,0,500,500));
		return circle; //Return textured circle for drawing
	}
	return circle; //Return empty circle
}

sf::RectangleShape Graphics::textureRect(string filepath, sf::Vector2f size)
{
	if (!texture.loadFromFile(filepath)) { //Try and load texture from designated filepath
		cout << "Unable to load texture from file."; //If it fails, display error message
	}
	else {
		texture.loadFromFile(filepath); //Load texture
		rect.setSize(size); //Set size to specified number
		rect.setTexture(&texture); //Apply texture to rectangle
		return rect; //Return textured rectangle for drawing
	}
	return rect; //Return empty rectangle
}
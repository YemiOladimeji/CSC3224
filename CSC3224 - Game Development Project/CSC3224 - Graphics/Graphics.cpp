#include "Graphics.h"

Graphics::Graphics() { //Default constructor

}

sf::Sprite Graphics::createBGMSprite(string filepath) {
	if (!texture.loadFromFile(filepath)) { //Try and load texture from file
		cout << "Unable to load texture from file."; //Output error message
	}
	else {
		texture.loadFromFile(filepath); //Load texture
		bgmSprite.setTexture(texture); //Apply texture to sprite
		return bgmSprite; //Return sprite for drawing
	}
	return bgmSprite; //Return empty sprite
}

sf::Sprite Graphics::clampSprite(sf::Sprite sprite, int left, int top, int width, int height)
{
	sprite.setTextureRect(sf::IntRect(left, top, width, height));
	return sprite;
}
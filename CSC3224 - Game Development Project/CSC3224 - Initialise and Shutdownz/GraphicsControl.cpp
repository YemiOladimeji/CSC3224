#include "GraphicsControl.h"

sf::Texture GraphicsControl::loadTexture(string filepath)
{
	if (!texture.loadFromFile(filepath)) {
		cout << "Could not load image file.";
	}
	else {
		texture.loadFromFile(filepath);
	}
	return texture;
}

sf::Sprite GraphicsControl::setSpriteTexture(sf::Texture spriteTexture)
{
	sprite.setTexture(spriteTexture);
	return sprite;
}

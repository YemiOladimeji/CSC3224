#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;

class Graphics {
private:
	sf::Texture texture; //Object to hold loaded textures for sprites
	sf::Sprite bgmSprite; //Object to be drawn to the screen with textures applied
	sf::Sprite pcSprite; //Object to be drawn to the screen with for player controlled characters

public:
	Graphics(); //Default constructor
	~Graphics() {}; //Destructor
	sf::Sprite createBGMSprite(string filepath); //Function to load and apply a static texture to a sprite
	sf::Sprite clampSprite(sf::Sprite sprite, int left, int top, int width, int height); //Function to cut a sprite sheet down to a specified size for animation
};

#endif // !GRAPHICS_H


#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML\Graphics.hpp>

using namespace std;

class Graphics {
private:
	sf::Texture texture; //Object to hold loaded textures for sprites
	sf::Sprite sprite; //Object to be drawn to the screen with textures applied

public:
	Graphics(); //Default constructor
	~Graphics() {}; //Destructor
	int loadTexture(); //Function to load and apply a texture to a sprite
};

#endif // !GRAPHICS_H


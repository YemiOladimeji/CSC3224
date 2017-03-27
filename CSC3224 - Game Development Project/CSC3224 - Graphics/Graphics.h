#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;

class Graphics {
private:
	sf::Texture texture; //Object to hold loaded textures for sprites
	sf::Sprite sprite; //Object to be drawn to the screen with textures applied
	sf::CircleShape circle; //Circle to be drawn on screen for testing purposes

public:
	Graphics(); //Default constructor
	~Graphics() {}; //Destructor
	sf::Sprite textureSprite(string filepath); //Function to load and apply a texture to a sprite
	sf::CircleShape textureCircle(string filepath); //Function to load and apply a texture to a circle

};

#endif // !GRAPHICS_H

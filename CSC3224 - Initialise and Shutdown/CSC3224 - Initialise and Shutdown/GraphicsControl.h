//Document management
#pragma once
#ifndef GRAPHICSCONTROL_H
#define GRAPHICSCONTROL_H

//Include statements
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class GraphicsControl {

private:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	sf::Texture loadTexture(string filepath);
	sf::Sprite setSpriteTexture(sf::Texture spriteTexture);
};


#endif //GraphicsControl
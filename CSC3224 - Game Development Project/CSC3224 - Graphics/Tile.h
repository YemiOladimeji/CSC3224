#pragma once
#ifndef TILE_H
#define TILE_H

#include <SFML\Graphics.hpp>

#include <vector>
#include <string>

#include "AnimationHandler.h"

using namespace std;

enum class TileType {
	VOID,
	GRASS,
	FOREST,
	WATER,
	RESIDENTIAL,
	COMMERCIAL,
	INDUSTRIAL,
	ROAD
};

string tileTypeToString(TileType type);

class Tile 
{
public:

	Tile(); //Default constructor
	Tile(const unsigned int tileSize, const unsigned int height, sf::Texture &texture, const std::vector<Animation> &animations, const TileType tileType, const unsigned int cost, const unsigned int maxPopPerLevel, const unsigned int maxLevels); //Parameterised constructor
	void draw(sf::RenderWindow &window, float deltaTime);
	void update();

	inline string getCost() { //Return a string containing the display cost of the tile
		return to_string(this->cost);
	}

	AnimationHandler handler;
	sf::Sprite sprite;
	TileType tileType;
	int tileVariant; //A tile variant allows for different versions of the same tile
	unsigned int regions[1];
	unsigned int cost, maxPopPerLevel, maxLevels;
	double population;
	float production, storedGoods;
};

#endif // !TILE_H


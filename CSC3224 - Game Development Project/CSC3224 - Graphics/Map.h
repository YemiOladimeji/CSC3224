#pragma once
#ifndef MAP_H
#define MAP_H

#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include <vector>
#include "Tile.h"

using namespace std;

class Map 
{
public:

	Map(); //Default constructor
	Map(const string &filename, unsigned int width, unsigned int height, map<string, Tile> &tiles); //Parameterised constructor

	unsigned int width, height, tileSize, numSelected;
	unsigned int numRegions[1];

	vector<Tile> tiles;
	vector<int> resources;
	vector<char> selected;

	void load(const string &filename, unsigned int width, unsigned int height, map<string, Tile> &tiles);
	void save(const string &filename);

	void draw(sf::RenderWindow &window, float deltaTime);
	void findConnectingRegions(vector<TileType> whitelist, int type);
	void updateDirection(TileType tileType);
	void select(sf::Vector2i start, sf::Vector2i end, vector<TileType> blacklist);
	void clearSelected();
	
private:
	void depthFirstSearch(vector<TileType> &whitelist, sf::Vector2i pos, int label, int type);
};

#endif // !MAP_H

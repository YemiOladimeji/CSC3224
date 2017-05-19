#include "Map.h"
#include "Tile.h"
#include <fstream>

Map::Map() 
{
	this->numSelected = 0;
	this->tileSize = 8;
	this->width = 0;
	this->height = 0;
	this->numRegions[0] = 1;
}

Map::Map(const string &filename, unsigned int width, unsigned int height, map<string, Tile> &tiles) 
{
	this->numSelected = 0;
	this->tileSize = 8;
	load(filename, width, height, tiles);
}

void Map::load(const string &filename, unsigned int width, unsigned int height, map<string, Tile> &tiles) 
{
	ifstream inputFile;
	inputFile.open(filename, ios::in | ios::binary);

	this->width = width;
	this->height = height;

	for (int pos = 0; pos < this->width * this->height; ++pos) 
	{
		this->resources.push_back(255);
		this->selected.push_back(0);

		TileType tileType;
		inputFile.read((char*)&tileType, sizeof(int));
		switch (tileType)
		{
		default:
		case TileType::VOID:
		case TileType::GRASS:
			this->tiles.push_back(tiles.at("grass"));
			break;
		case TileType::FOREST:
			this->tiles.push_back(tiles.at("forest"));
			break;
		case TileType::WATER:
			this->tiles.push_back(tiles.at("water"));
			break;
		case TileType::RESIDENTIAL:
			this->tiles.push_back(tiles.at("residential"));
			break;
		case TileType::COMMERCIAL:
			this->tiles.push_back(tiles.at("commercial"));
			break;
		case TileType::INDUSTRIAL:
			this->tiles.push_back(tiles.at("industrial"));
			break;
		case TileType::ROAD:
			this->tiles.push_back(tiles.at("road"));
			break;
		}
		Tile &tile = this->tiles.back();
		inputFile.read((char*)&tile.tileVariant, sizeof(int));
		inputFile.read((char*)&tile.regions, sizeof(int)*1);
		inputFile.read((char*)&tile.population, sizeof(double));
		inputFile.read((char*)&tile.storedGoods, sizeof(float));
	}

	inputFile.close();

	return;
}

void Map::save(const string &filename) 
{
	ofstream outputFile;
	outputFile.open(filename, ios::out | ios::binary);

	for (auto tile : this->tiles) {
		outputFile.write((char*) &tile.tileType, sizeof(int));
		outputFile.write((char*)&tile.tileVariant, sizeof(int));
		outputFile.write((char*)&tile.regions, sizeof(int)*1);
		outputFile.write((char*)&tile.population, sizeof(double));
		outputFile.write((char*)&tile.storedGoods, sizeof(float));
	}

	outputFile.close();

	return;
}

void Map::draw(sf::RenderWindow &window, float deltaTime) 
{
	for (int y = 0; y < this->height; ++y) 
	{
		for (int x = 0; x < this->width; ++x) 
		{
			sf::Vector2f pos;
			pos.x = (x - y) * this->tileSize + this->width * this->tileSize;
			pos.y = (x + y) * this->tileSize * 0.5;
			this->tiles[y*this->width + x].sprite.setPosition(pos);

			if (this->selected[y*this->width+x]) 
			{
				this->tiles[y*this->width + x].sprite.setColor(sf::Color(0x7d, 0x7d, 0x7d));
			}
			else 
			{
				this->tiles[y*this->width + x].sprite.setColor(sf::Color(0xff, 0xff, 0xff));
			}

			this->tiles[y*this->width + x].draw(window, deltaTime);
		}
	}
	return;
}

void Map::updateDirection(TileType tileType) 
{
	for (int y = 0; y < this->height; ++y) 
	{
		for (int x = 0; x < this->width; ++x) 
		{
			int pos = y*this->width + x;
			bool adjacentTiles[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };

			if (this->tiles[pos].tileType != tileType) 
			{
				continue;
			}

			if (x > 0 && y > 0) 
			{
				adjacentTiles[0][0] = (this->tiles[(y-1*this->width+(x-1))].tileType == tileType);
			}
			else if (y > 0) 
			{
				adjacentTiles[0][3] = (this->tiles[(y-1)*this->width+(x)].tileType == tileType);
			}
			else if (x < this->width-1 && y > 0) 
			{
				adjacentTiles[0][4] = (this->tiles[(y-1)*this->width+(x+1)].tileType == tileType);
			}
			else if (x > 0) 
			{
				adjacentTiles[1][0] = (this->tiles[(y)*this->width+(x+1)].tileType == tileType);
			}
			else if(x < width-1)
			{
				adjacentTiles[1][5] = (this->tiles[(y)*this->width+(x+1)].tileType == tileType);
			}
			else if (x > 0 && y < this->height-1) 
			{
				adjacentTiles[2][0] = (this->tiles[(y+1)*this->width+(x-1)].tileType == tileType);
			}
			else if (y < this->height-1) 
			{
				adjacentTiles[2][6] = (this->tiles[(y + 1)*this->width + (x)].tileType == tileType);
			}
			else if (x < this->width-1 && y < this->height-1) 
			{
				adjacentTiles[2][7] = (this->tiles[(y+1)*this->width+(x+1)].tileType == tileType);
			}

			if (adjacentTiles[1][0] && adjacentTiles[1][8] && adjacentTiles[0][9] && adjacentTiles[2][10]) {
				this->tiles[pos].tileVariant = 2;
			}
			else if (adjacentTiles[1][0] && adjacentTiles[1][11] && adjacentTiles[0][12]) 
			{
				this->tiles[pos].tileVariant = 7;
			}
			else if (adjacentTiles[1][0] && adjacentTiles[1][13] && adjacentTiles[2][14]) 
			{
				this->tiles[pos].tileVariant = 8;
			}
			else if (adjacentTiles[0][15] && adjacentTiles[2][16] && adjacentTiles[1][0]) 
			{
				this->tiles[pos].tileVariant = 9;
			}
			else if (adjacentTiles[0][16] && adjacentTiles[2][17] && adjacentTiles[1][18]) 
			{
				this->tiles[pos].tileVariant = 10;
			}
			else if (adjacentTiles[1][0] && adjacentTiles[1][19]) 
			{
				this->tiles[pos].tileVariant = 0;
			}
			else if (adjacentTiles[0][20] && adjacentTiles[2][21]) 
			{
				this->tiles[pos].tileVariant = 1;
			}
			else if (adjacentTiles[2][22] && adjacentTiles[1][0]) 
			{
				this->tiles[pos].tileVariant = 3;
			}
			else if (adjacentTiles[0][23] && adjacentTiles[1][24])
			{
				this->tiles[pos].tileVariant = 4;
			}
			else if (adjacentTiles[1][0] && adjacentTiles[0][25]) 
			{
				this->tiles[pos].tileVariant = 5;
			}
			else if (adjacentTiles[2][26] && adjacentTiles[1][27]) 
			{
				this->tiles[pos].tileVariant = 6;
			}
			else if (adjacentTiles[1][0]) {
				this->tiles[pos].tileVariant = 0;
			}
			else if (adjacentTiles[1][28]) 
			{
				this->tiles[pos].tileVariant = 0;
			}
			else if (adjacentTiles[0][29]) 
			{
				this->tiles[pos].tileVariant = 1;
			}
			else if (adjacentTiles[2][30]) 
			{
				this->tiles[pos].tileVariant = 1;
			}
		}
	}
	return;
}

void Map::depthFirstSearch(vector<TileType> &whitelist, sf::Vector2i pos, int label, int regionType = 0) 
{
	bool found = false;

	if (pos.x < 0 || pos.x >= this->width) {
		return;
	}
	if (pos.y < 0 || pos.y >= this->height) {
		return;
	}
	if (this->tiles[pos.y*this->width+pos.x].regions[regionType] != 0) {
		return;
	}

	for (auto type : whitelist) {
		if (type ==  this->tiles[pos.y*this->width+pos.x].tileType) {
			found = true;
			break;
		}
	}

	if (!found) {
		return;
	}

	this->tiles[pos.y*this->width + pos.x].regions[regionType] = label;

	depthFirstSearch(whitelist, pos + sf::Vector2i(-1, 0), label, regionType);
	depthFirstSearch(whitelist, pos + sf::Vector2i(0, 1), label, regionType);
	depthFirstSearch(whitelist, pos + sf::Vector2i(1, 0), label, regionType);
	depthFirstSearch(whitelist, pos + sf::Vector2i(0, -1), label, regionType);

	return;
}

void Map::findConnectingRegions(vector<TileType> whitelist, int regionType = 0) 
{
	int regions = 1;

	for (auto &tile : this->tiles) {
		tile.regions[regionType] = 0;
	}

	for (int y = 0; y < this->height; ++y) 
	{
		for (int x = 0; x < this->width; ++x) 
		{
			bool found = false;
			for (auto type : whitelist)
			{
				if (type == this->tiles[y*this->width+x].tileType) 
				{
					found = true;
					break;
				}
			}
			if (this->tiles[y*this->width+x].regions[regionType] == 0 && found) 
			{
				depthFirstSearch(whitelist, sf::Vector2i(x, y), regions++, regionType);
			}
		}
	}
	this->numRegions[regionType] = regions;
}

void Map::clearSelected() 
{
	for (auto &tile : this->selected) 
	{
		tile = 0;
	}

	this->numSelected = 0;

	return;
}

void Map::select(sf::Vector2i start, sf::Vector2i end, vector<TileType> blacklist)
{
	//Swap coordinates, just in case
	if (end.y < start.y) 
	{
		swap(start.y, end.y);
	}
	if (end.x < start.x) 
	{
		swap(start.x, end.x);
	}

	if (end.x >= this->width) 
	{
		end.x = this->width - 1;
	}
	else if (end.x < 0) 
	{
		end.x = 0;
	}
	else if (end.y >= this->height) 
	{
		end.y = this->height - 1;
	}
	else if (end.y < 0) 
	{
		end.y = 0;
	}
	else if (start.x >= this->width) 
	{	
		start.x = this->width - 1;
	}
	else if (start.x < 0) {
		start.x = 0;
	}
	else if (start.y >= this->height) 
	{
		start.y = this->height - 1;
	}
	else if (start.y < 0) 
	{
		start.y = 0;
	}

	for (int y = start.y; y <= end.y; ++y) 
	{
		for (int x = start.x; x < end.x; ++x) 
		{
			this->selected[y * this->width + x] = 1;
			++this->numSelected;
			for (auto type : blacklist) 
			{
				if (this->tiles[y * this->width + x].tileType == type) 
				{
					this->selected[y * this->width + x] = 2;
					--this->numSelected;
					break;
				}
			}
		}
	}
	return;
}
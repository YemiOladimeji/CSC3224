#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <numeric>

#include "City.h"
#include <Tile.h>

void City::load(string cityName, std::map<std::string, Tile> &tiles)
{
	int width = 0;
	int height = 0;

	std::ifstream inputFile(cityName + "_cfg.dat", std::ios::in);

	string line;

	while (std::getline(inputFile, line))
	{
		std::istringstream lineStream(line);
		std::string key;
		if (std::getline(lineStream, key, '='))
		{
			std::string value;
			if (std::getline(lineStream, value))
			{
				if (key == "width") 
				{
					width = std::stoi(value);
				}
				else if (key == "height") 
				{
					height = std::stoi(value);
				}
				else if (key == "day") 
				{
					this->day = std::stoi(value);
				}
				else if (key == "populationPool") 
				{
					this->populationPool = std::stod(value);
				}
				else if (key == "employmentPool") 
				{
					this->employmentPool = std::stod(value);
				}
				else if (key == "population") 
				{
					this->population = std::stod(value);
				}
				else if (key == "employable") 
				{
					this->employable = std::stod(value);
				}
				else if (key == "birthRate") 
				{
					this->birthRate = std::stod(value);
				}
				else if (key == "deathRate") 
				{
					this->deathRate = std::stod(value);
				}
				else if (key == "residentialTax") 
				{
					this->residentialTax = std::stod(value);
				}
				else if (key == "commercialTax") 
				{
					this->commercialTax = std::stod(value);
				}
				else if (key == "industrialTax") 
				{
					this->industrialTax = std::stod(value);
				}
				else if (key == "funds") 
				{
					this->funds = std::stod(value);
				}
				else if (key == "earnings") 
				{
					this->earnings = std::stod(value);
				}
			}
			else
			{
				std::cerr << "Error: No value for key " << key << std::endl;
			}
		}
	}

	inputFile.close();
	this->map.load(cityName + "_map.dat", width, height, tiles);
	tileChanged();

	return;

}

void City::save(string cityName)
{
	std::ofstream outputFile(cityName + "_cfg.dat", std::ios::out);

	outputFile << "width=" << this->map.width << std::endl;
	outputFile << "height=" << this->map.height << std::endl;
	outputFile << "day=" << this->day << std::endl;
	outputFile << "populationPool=" << this->populationPool << std::endl;
	outputFile << "employmentPool=" << this->employmentPool << std::endl;
	outputFile << "population=" << this->population << std::endl;
	outputFile << "employable=" << this->employable << std::endl;
	outputFile << "birthRate=" << this->birthRate << std::endl;
	outputFile << "deathRate=" << this->deathRate << std::endl;
	outputFile << "residentialTax=" << this->residentialTax << std::endl;
	outputFile << "commercialTax=" << this->commercialTax << std::endl;
	outputFile << "industrialTax=" << this->industrialTax << std::endl;
	outputFile << "funds=" << this->funds << std::endl;
	outputFile << "earnings=" << this->earnings << std::endl;

	outputFile.close();

	this->map.save(cityName + "_map.dat");

	return;
}

void City::update(float dt)
{
	double popTotal = 0;
	double commercialRevenue = 0;
	double industrialRevenue = 0;

	//Update game time
	this -> currentTime += dt;
	if (this->currentTime < this->timePerDay) 
	{
		return;
	}
	++day;
	this->currentTime = 0.0;
	if(day % 30 == 0) 
	{
		this->funds += this->earnings;
		this->earnings = 0;
	}

	//Handle pool distribution
	for (int i = 0; i < this->map.tiles.size()-1; ++i) 
	{
		Tile &tile = this->map.tiles[this->shuffledTiles[i]];

		if (tile.tileType == TileType::RESIDENTIAL) 
		{
			this->distributePool(this->populationPool, tile, this->birthRate - this->deathRate);
			popTotal += tile.population;
		}
		else if (tile.tileType == TileType::COMMERCIAL) 
		{
			if (rand() % 100 < 15 * (1.0-this->commercialTax)) 
			{
				this->distributePool(this->employmentPool, tile, 0.00);
			}
		}
		else if (tile.tileType == TileType::INDUSTRIAL) 
		{
			if (this->map.resources[i] > 0 && rand() % 100 < this->population) 
			{
				++tile.production;
				--this->map.resources[i];
				if (rand() % 100 < 15 * (1.0-this->industrialTax)) {
					this->distributePool(this->employable, tile, 0.00);
				}
			}
		}
		tile.update();
	}

	//Handle goods manufacturing
	for (int i = 0; i < this->map.tiles.size()-1; ++i) 
	{
		Tile &tile = this->map.tiles[this->shuffledTiles[i]];

		if (tile.tileType == TileType::INDUSTRIAL) 
		{
			int recievedResources = 0;
			for (auto &tile2 : this->map.tiles) 
			{
				if (tile2.regions[0] == tile.regions[0] && tile2.tileType == TileType::INDUSTRIAL) 
				{
					if (tile2.production > 0) 
					{
						++recievedResources;
						--tile2.production;
					}
					if (recievedResources >= tile.tileVariant+1) 
					{
						break;
					}
				}
			}
			tile.storedGoods += (recievedResources + tile.population) * (tile.tileVariant + 1);
		}
	}

	//Handle goods distribution
	for (int i = 0; i < this->map.tiles.size()-1; ++i) 
	{
		Tile &tile = this->map.tiles[this->shuffledTiles[i]];

		if (tile.tileType == TileType::COMMERCIAL) 
		{
			int recievedGoods = 0;
			double maxCustomers = 0.0;


			for (auto &tile2 : this->map.tiles)
			{
				if (tile2.regions[0] == tile.regions[0] && tile2.tileType == TileType::INDUSTRIAL && tile2.storedGoods > 0)
				{
					while (tile2.storedGoods > 0 && recievedGoods != tile.tileVariant + 1)
					{
						--tile2.storedGoods;
						++recievedGoods;
						industrialRevenue += 100 * (1.0 - industrialTax);
					}
				}
				else if (tile2.regions[0] == tile.regions[0] && tile2.tileType == TileType::RESIDENTIAL)
				{
					maxCustomers += tile2.population;
				}
				if (recievedGoods == tile.tileVariant + 1)
				{
					break;
				}
			}
			tile.production = (recievedGoods * 100.0 + rand() % 20) * (1.0 - this->commercialTax);

			double revenue = tile.production * maxCustomers * tile.population / 100.0;
			commercialRevenue += revenue;
		}
	}

	this->populationPool += this->populationPool * (this->birthRate - this->deathRate);
	popTotal += this->populationPool;

	float newWorkers = (popTotal - this->population) * this->propCanWork;
	newWorkers *= newWorkers < 0 ? -1 : 1;
	this->employmentPool += newWorkers;
	this->employable += newWorkers;
	if (this->employmentPool < 0) 
	{
		this->employmentPool = 0;
	}
	if (this->employable < 0) 
	{
		this->employable = 0;
	}

	this->population = popTotal;

	this->earnings = (this->population - this->populationPool) * 15 * this->residentialTax;
	this->earnings += commercialRevenue * this->commercialTax;
	this->earnings += industrialRevenue * this->industrialTax;

	return;
}

void City::bulldoze(const Tile &tile)
{
	for (int pos = 0; pos < (this->map.width * this->map.height); ++pos) 
	{
		if (this->map.selected[pos] == 1) 
		{
			if (this->map.tiles[pos].tileType == TileType::RESIDENTIAL) 
			{
				this->populationPool += this->map.tiles[pos].population;
			}
			else if (this->map.tiles[pos].tileType == TileType::COMMERCIAL) 
			{
				this->employmentPool += this->map.tiles[pos].population;
			}
			else if (this->map.tiles[pos].tileType == TileType::INDUSTRIAL) 
			{
				this->employmentPool += this->map.tiles[pos].population;
			}
			this->map.tiles[pos] = tile;
		}
	}
	return;
}

void City::shuffleTiles()
{
	while (this->shuffledTiles.size() < this->map.tiles.size()) 
	{
		this->shuffledTiles.push_back(0);
	}
	std::iota(shuffledTiles.begin(), shuffledTiles.end(), 0);
	std::random_shuffle(shuffledTiles.begin(), shuffledTiles.end());
	
	return;
}

void City::tileChanged()
{
	this->map.updateDirection(TileType::ROAD);
	this->map.findConnectingRegions({TileType::ROAD, TileType::RESIDENTIAL, TileType::COMMERCIAL, TileType::INDUSTRIAL}, 0);

	return;
}

double City::distributePool(double &pool, Tile &tile, double rate = 0.0)
{
	const static int MOVE_RATE = 4;

	unsigned int maxPop = tile.maxPopPerLevel * (tile.tileVariant + 1);

	if (pool > 0) 
	{
		int moving = maxPop - tile.population;

		if (moving > MOVE_RATE) 
		{
			moving = MOVE_RATE;
		}

		if (pool - moving < 0) 
		{
			moving = pool;
		}

		pool -= moving;
		tile.population += moving;
	}

	tile.population += tile.population * rate;

	if (tile.population > maxPop) 
	{
		pool += tile.population - maxPop;
		tile.population = maxPop;
	}

	return tile.population;
}

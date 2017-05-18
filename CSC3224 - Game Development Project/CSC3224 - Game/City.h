#pragma once
#ifndef CITY_H
#define CITY_H

#include <vector>
#include <map>
#include "Map.h"

using namespace std;

class City 
{
public:
	City() //Default constructor
	{
		this->birthRate = 0.00055;
		this->deathRate = 0.00023;
		this->propCanWork = 0.50;
		this->populationPool = 0;
		this->population = populationPool;
		this->employmentPool = 0;
		this->employable = employmentPool;
		this->residentialTax = 0.05;
		this->commercialTax = 0.05;
		this->industrialTax = 0.05;
		this->earnings = 0;
		this->funds = 0;
		this->currentTime = 0.0;
		this->timePerDay = 1.0;
		this->day = 0;
	}

	City(string cityName, int tileSize, std::map<string, Tile> &tiles) : City() 
	{
		this->map.tileSize = tileSize;
		load(cityName, tiles);
	}

	virtual ~City() {};

	Map map;

	double population, employable, residentialTax, commercialTax, industrialTax, earnings, funds;

	int day;

	void load(string cityName, std::map<string, Tile> &tileAtlas);
	void save(string cityName);

	void update(float dt);
	void bulldoze(const Tile &tile);
	void shuffleTiles();
	void tileChanged();

	inline double getHomeless() {
		return this->populationPool;
	}
	
	inline double getUnemployed() {
		return this->employmentPool;
	}

private:
	float currentTime, timePerDay, propCanWork;

	std::vector<int> shuffledTiles;

	double populationPool, employmentPool, birthRate, deathRate;

	double distributePool(double &pool, Tile &tile, double rate);
};

#endif // !CITY_H


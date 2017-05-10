#include "City.h"

City::City()
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

City::City(string cityName, int tileSize, map<string, Tile>& tiles) : City()
{
	this->map.tileSize = tileSize;
	load(cityName, tiles);
}

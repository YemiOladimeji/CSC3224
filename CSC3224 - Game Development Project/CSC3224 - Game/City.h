#pragma once
#ifndef CITY_H
#define CITY_H

#include <vector>
#include <map>
#include <Map.h>

using namespace std;

class City 
{
public:
	City(); //Default constructor
	City(string cityName, int tileSize, map<string, Tile> &tiles) : City();
	virtual ~City() {};

	Map map;

	double population, employable, residentialTax, commercialTax, industrialTax, earnings, funds;

	int day;

	void load(string cityName, map<string, Tile> &tileAtlas);
	void save(string cityName);


private:
	float currentTime, timePerDay;

	std::vector<int> shuffledTiles;


	double populationPool, employmentPool, propCanWork, birthRate, deathRate;

	double distributePool(double &pool, Tile &tile, double rate);

};

#endif // !CITY_H


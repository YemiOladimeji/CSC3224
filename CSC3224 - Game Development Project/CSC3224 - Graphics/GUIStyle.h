#pragma once
#ifndef GUISTYLE_H
#define GUISTYLE_H

#include<SFML\Graphics.hpp>

#include <vector>
#include <utility>
#include <string>

using namespace std;

class GUIStyle 
{
public:
	
	GUIStyle(); //Default constructor
	GUIStyle(sf::Font *font, float borderSize, sf::Color bodyCol, sf::Color borderCol, sf::Color textCol, sf::Color bodyHighlightCol, sf::Color borderHighlightCol, sf::Color textHighlightCol); //Paramterised constructor
	virtual ~GUIStyle() {}; //Destructor

	sf::Color bodyCol,bodyHighlightCol, borderCol, borderHighlightCol, textCol, textHighlightCol;
	sf::Font* font;

	float borderSize;
};

#endif // !GUI_H


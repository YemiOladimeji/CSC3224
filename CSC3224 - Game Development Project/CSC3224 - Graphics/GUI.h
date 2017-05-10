#pragma once
#ifndef GUI_H
#define GUI_H

#include<SFML\Graphics.hpp>

#include <vector>
#include <utility>
#include <string>
#include "GUIStyle.h"
#include "GUIEntry.h"

using namespace std;

class GUI : public sf::Transformable
{
public:
	GUI(); //Default constructor
	GUI(sf::Vector2f dimensions, int padding, bool horizontal, GUIStyle &style, vector<pair<string, string>> entries); //Parameterised constructor
	virtual ~GUI() {}; //Destructor

	vector<GUIEntry> entries;
	bool visible;

	sf::Vector2f getSize();
	int getEntry(const sf::Vector2f mousePos);
	void setEntryText(int entry, string text);
	void setDimensions(sf::Vector2f dimensions);

	virtual const void draw(sf::RenderTarget &target, sf::RenderStates states);

	void show();
	void hide();
	void highlight(const int entry);

	string activate(const int entry);
	string activate(const sf::Vector2f mousePos);

private:
	bool horizontal;
	GUIStyle style;
	sf::Vector2f dimensions;
	int padding;
};

#endif // !GUI_H


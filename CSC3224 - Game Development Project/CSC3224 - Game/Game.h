#pragma once
#ifndef GAME_H
#define GAME_H

#include <stack>
#include <SFML\Graphics.hpp>
#include <Texture.h>
#include "Tile.h"
#include <GUIStyle.h>

using namespace std;

class GameState;

class Game
{
public:
	Game(); //Default constructor
	virtual ~Game(); //Destructor

	const static int TILE_SIZE = 8;
	stack<GameState*> states; //Stack data structure to store GameStates
	sf::RenderWindow window; //SFML RenderWindow object
	Texture manager;
	sf::Sprite background;

	map<string, Tile> tiles;
	map<string, GUIStyle> styles;
	map<string, sf::Font> fonts;

	void pushState(GameState* state); //Function which takes a pointer to a state and pushes it onto the stack
	void popState(); //Function which removes the top state from the stack
	void changeState(GameState* state); //Functon which pops the previous state and then pushes on a new one
	GameState* peekState(); //Function which returns a pointer to whatever state is on the stack

	void gameLoop(); //Function to run the game

private:
	void loadTextures();
	void loadTiles();
	void loadStyles();
	void loadFonts();
};

#endif // !GAME_H

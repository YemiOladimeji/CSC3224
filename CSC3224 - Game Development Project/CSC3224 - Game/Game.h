#pragma once
#ifndef GAME_H
#define GAME_H

#include <stack>
#include <SFML\Graphics.hpp>

using namespace std;

class GameState;

class Game
{
public:
	Game(); //Default constructor
	virtual ~Game() {}; //Destructor

	stack<GameState*> states; //Stack data structure to store GameStates
	sf::RenderWindow window; //SFML RenderWindow object

	void pushState(GameState* state); //Function which takes a pointer to a state and pushes it onto the stack
	void popState(); //Function which removes the top state from the stack
	void changeState(GameState* state); //Functon which pops the previous state and then pushes on a new one
	GameState* peekState(); //Function which returns a pointer to whatever state is on the stack

	void gameLoop(); //Function to run the game

private:

};

#endif // !GAME_H

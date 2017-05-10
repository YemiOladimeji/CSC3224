#pragma once
#ifndef GAME_STATE_START_H
#define GAME_STATE_START_H

#include <SFML\Graphics.hpp>
#include "GameState.h"
#include <utility>
#include <GUI.h>

class GameStateStart : public GameState
{
public:
	GameStateStart(Game* game);

	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

private:
	sf::View view;
	map<string, GUI> GUISystem;
	void loadGame();
};

#endif // !GAME_STATE_START_H

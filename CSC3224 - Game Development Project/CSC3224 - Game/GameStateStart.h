#pragma once
#ifndef GAME_STATE_START_H
#define GAME_STATE_START_H

#include <SFML\Graphics.hpp>
#include "GameState.h"

class GameStateStart : public GameState
{
public:
	GameStateStart(Game* game);

	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

private:
	sf::View view;
	void loadGame();
};

#endif // !GAME_STATE_START_H

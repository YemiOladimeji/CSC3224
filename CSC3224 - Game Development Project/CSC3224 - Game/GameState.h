#pragma once
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Game.h"

class GameState 
{
public:
	Game* game;

	virtual void draw(const float deltaTime) = 0;
	virtual void update(const float deltaTime) = 0;
	virtual void handleInput() = 0;
};

#endif // !GAME_STATE_h

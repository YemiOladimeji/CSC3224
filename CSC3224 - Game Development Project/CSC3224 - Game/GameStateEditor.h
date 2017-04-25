#pragma once
#ifndef GAME_STATE_EDITOR_H
#define GAME_STATE_EDITOR_H

#include <SFML\Graphics.hpp>
#include "GameState.h"

class GameStateEditor : public GameState 
{
public:
	GameStateEditor(Game* game);

	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

private:
	sf::View gameView;
	sf::View guiView;
};
#endif // !GAME_STATE_EDITOR_H

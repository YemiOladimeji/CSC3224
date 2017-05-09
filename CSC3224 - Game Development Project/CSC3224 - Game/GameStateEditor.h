#pragma once
#ifndef GAME_STATE_EDITOR_H
#define GAME_STATE_EDITOR_H

#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Map.h"

enum class ActionState 
{
	NONE,
	PANNING,
	SELECTING
};

class GameStateEditor : public GameState 
{
public:
	GameStateEditor(Game* game);

	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);
	virtual void handleInput();

private:
	sf::View gameView, guiView;
	Map map;
	ActionState actionState;
	sf::Vector2i panningAnchor, selectionStart, selectionEnd;
	float zoomLevel;
	Tile* currentTile;
};
#endif // !GAME_STATE_EDITOR_H

#include "Game.h"
#include "GameState.h"
#include <SFML\System.hpp>

void Game::pushState(GameState* state) 
{
	this->states.push(state);
	return;
}

void Game::popState() 
{
	delete this->states.top();
	this->states.pop();
	return;
}

void Game::changeState(GameState* state) 
{
	if (!this->states.empty()) {
		popState();
	}
	else 
	{
		pushState(state);
		return;
	}
	return;
}

GameState* Game::peekState() 
{
	if (this->states.empty()) {
		return nullptr;
	}
	else 
	{
		return this->states.top();
	}
}

void Game::gameLoop() 
{
	sf::Clock clock;

	while (this->window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();

		if (peekState() == nullptr) {
			continue;
		}
		else {
			peekState()->handleInput();
			peekState()->update(deltaTime);
			this->window.clear(sf::Color::Black);
			peekState()->draw(deltaTime);
			this->window.display();
		}
	}
}

Game::Game() {
	this->window.create(sf::VideoMode(720, 480), "CSC3224 - City Builder");
	this->window.setFramerateLimit(60);
}

Game::Game() 
{
	while (!this->states.empty()) {
		popState();
	}
}
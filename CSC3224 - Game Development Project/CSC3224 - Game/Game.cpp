#include "Game.h"
#include "GameState.h"
#include <Texture.h>
#include <Animation.h>
#include <BGM.h>
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

void Game::loadTextures()
{
	this->manager.loadTexture("background", "Images\\background.png");
	this->manager.loadTexture("grass", "Images\\grass.png");
	this->manager.loadTexture("forest", "Images\\forest.png");
	this->manager.loadTexture("water", "Images\\water.png");
	this->manager.loadTexture("residential", "Images\\residential.png");
	this->manager.loadTexture("commercial", "Images\\commercial.png");
	this->manager.loadTexture("industrial", "Images\\industrial.png");
	this->manager.loadTexture("road", "Images\\road.png");
}

void Game::loadTiles() 
{
	Animation staticAnim(0, 0, 1.0f);

	this->tiles["grass"] = Tile(this->TILE_SIZE, 1, manager.getTexRef("grass"), {staticAnim}, TileType::GRASS, 50, 0, 1);
	this->tiles["forest"] = Tile(this->TILE_SIZE, 1, manager.getTexRef("forest"), { staticAnim }, TileType::FOREST, 100, 0, 1);
	this->tiles["water"] = Tile(this->TILE_SIZE, 1, manager.getTexRef("water"), { Animation(0, 3, 0.5f), Animation(0, 3, 0.5f), Animation(0, 3, 0.5f) }, TileType::GRASS, 0, 0, 1);
	this->tiles["residential"] = Tile(this->TILE_SIZE, 2, manager.getTexRef("residential"), { staticAnim, staticAnim, staticAnim, staticAnim, staticAnim, staticAnim }, TileType::RESIDENTIAL, 300, 50, 6);
	this->tiles["commercial"] = Tile(this->TILE_SIZE, 2, manager.getTexRef("commercial"), { staticAnim, staticAnim, staticAnim, staticAnim }, TileType::COMMERCIAL, 300, 50, 4);
	this->tiles["industrial"] = Tile(this->TILE_SIZE, 2, manager.getTexRef("industrial"), { staticAnim, staticAnim, staticAnim, staticAnim }, TileType::INDUSTRIAL, 300, 50, 4);
	this->tiles["road"] = Tile(this->TILE_SIZE, 1, manager.getTexRef("road"), { staticAnim, staticAnim, staticAnim, staticAnim, staticAnim, staticAnim, staticAnim , staticAnim, staticAnim, staticAnim, staticAnim }, TileType::ROAD, 100, 0, 1);
	return;
}

void Game::loadFonts() 
{
	sf::Font font;
	font.loadFromFile("Fonts\\font.ttf");
	this->fonts["mainFont"] = font;

	return;
}

void Game::loadAudio()
{
	music.loadBGM("Audio Files\\bgm.flac");
}

void Game::loadStyles() {
	this->styles["button"] = GUIStyle(&this->fonts.at("mainFont"), 1, sf::Color(0xc6, 0xc6, 0xc6), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00), sf::Color(0x61, 0x61, 0x61), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00));
	this->styles["text"] = GUIStyle(&this->fonts.at("mainFont"), 0, sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00), sf::Color(0xff, 0xff, 0xff), sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00), sf::Color(0xff, 0x00, 0x00));

	return;
}

Game::Game() {
	this->loadTextures();
	this->loadTiles();
	this->loadFonts();
	this->loadStyles();
	this->loadAudio();
	this->window.create(sf::VideoMode(720, 480), "CSC3224 - CitySim");
	this->window.setFramerateLimit(60);
	this->background.setTexture(this->manager.getTexRef("background"));
}

Game::~Game() 
{
	while (!this->states.empty()) {
		popState();
	}
}
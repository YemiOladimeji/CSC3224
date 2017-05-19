#include <SFML\Graphics.hpp>

#include "GameStateEditor.h"
#include "GameStateStart.h"
#include "GameState.h"

GameStateStart::GameStateStart(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	this->GUISystem.emplace("menu", GUI(sf::Vector2f(192, 32), 4, false, this->game->styles.at("button"), {std::make_pair(" Start Game", "loadGame")}));

	this->GUISystem.at("menu").setPosition(pos);
	this->GUISystem.at("menu").setOrigin(96, 32 * 0.5);
	this->GUISystem.at("menu").show();
}


void GameStateStart::draw(const float deltaTime)
{
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	for (auto GUI : this->GUISystem) {
		this->game->window.draw(GUI.second);
	}
	
	return;
}

void GameStateStart::update(const float deltaTime)
{
	return;
}

void GameStateStart::handleInput()
{
	sf::Event event;

	sf::Vector2f mousePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->view);

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->game->window.close();
			break;
		case sf::Event::Resized:
			this->view.setSize(event.size.width, event.size.height);
			this->view.setCenter(event.size.width * 0.5, event.size.height * 0.5);
			this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0,0)));
			this->game->background.setScale(
				float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
				float(event.size.height) / float (this->game->background.getTexture()->getSize().y));
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				this->game->window.close();
			}
			else if (event.key.code == sf::Keyboard::Return) {
				this->loadGame();
			}
				break;
		case sf::Event::MouseMoved:
			this->GUISystem.at("menu").highlight(this->GUISystem.at("menu").getEntry(mousePos));
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				string msg = this->GUISystem.at("menu").activate(mousePos);

				if (msg == "loadGame")
				{
					this->loadGame();
				}
			}
			break;
		default:
			break;
		}
	}
	return;
}

void GameStateStart::loadGame() {
	this->game->pushState(new GameStateEditor(this->game));
	return;
}
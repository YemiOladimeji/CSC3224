#include <SFML\Graphics.hpp>
#include "GameStateEditor.h"
#include "GameStateStart.h"
#include "GameState.h"

GameStateStart::GameStateStart(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	this->GUISystem.emplace("menu", GUI(sf::Vector2f(192, 32), 4, false, game->styles.at("button"), {std::make_pair("Load Game", "loadGame")}));

	this->GUISystem.at("menu").setPosition(pos);
	this->GUISystem.at("menu").setOrigin(96, 32 * 0.5);
	this->GUISystem.at("menu").show();
}


void GameStateStart::draw(const float deltaTime)
{
	game->window.setView(this->view);

	game->window.clear(sf::Color::Black);
	game->window.draw(game->background);

	for (auto GUI : this->GUISystem) {
		game->window.draw(GUI.second);
	}
	
	return;
}

void GameStateStart::update(const float deltaTime)
{

}

void GameStateStart::handleInput()
{
	sf::Event event;

	sf::Vector2f mousePos = game->window.mapPixelToCoords(sf::Mouse::getPosition(game->window), this->view);

	while (game->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			game->window.close();
			break;
		case sf::Event::Resized:
			this->view.setSize(event.size.width, event.size.height);
			this->view.setCenter(event.size.width * 0.5, event.size.height * 0.5);
			game->background.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0,0)));
			game->background.setScale(float(event.size.width)/float(game->background.getTexture()->getSize().x),
			float(event.size.height) / float (game->background.getTexture()->getSize().y));
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				game->window.close();
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
	game->pushState(new GameStateEditor(game));
	return;
}
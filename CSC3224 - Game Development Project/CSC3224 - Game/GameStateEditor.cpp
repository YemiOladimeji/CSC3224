#include <SFML\Graphics.hpp>

#include "GameStateEditor.h"
#include "GameState.h"
#include <Map.h>

GameStateEditor::GameStateEditor(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);

	this->city = City("city", this->game->TILE_SIZE, this->game->tiles);
	this->city.shuffleTiles();

	this->guiSystem.emplace("rightClickMenu", GUI(sf::Vector2f(196, 16), 2, false, this->game->styles.at("button"), 
	{
		std::make_pair("Flatten: �" + this->game->tiles["grass"].getCost(), "grass"),
		std::make_pair("Forest: �" + this->game->tiles["forest"].getCost(), "forest"),
		std::make_pair("Residential Zone: �" + this->game->tiles["residential"].getCost(), "residential"),
		std::make_pair("Commercial Zone: �" + this->game->tiles["commercial"].getCost(), "commercial"),
		std::make_pair("Industrial Zone: �" + this->game->tiles["industrial"].getCost(), "industrial"),
		std::make_pair("Road: �" + this->game->tiles["road"].getCost(), "road"),
	}));

	this->guiSystem.emplace("selectionCostText", GUI(sf::Vector2f(196, 16), 0, false, this->game->styles.at("text"), 
	{
		std::make_pair("", "")
	}));

	this->guiSystem.emplace("infoBar", GUI(sf::Vector2f((float)(this->game->window.getSize().x / 5), 16), 2, true, this->game->styles.at("button"),
	{
		std::make_pair("time", "time"),
		std::make_pair("funds", "funds"),
		std::make_pair("population", "population"),
		std::make_pair("employment", "employment"),
		std::make_pair("current tile", "tile")
	}));

	this->guiSystem.at("infoBar").setPosition(sf::Vector2f(0, (float)(this->game->window.getSize().y - 16)));
	this->guiSystem.at("infoBar").show();

	this->zoomLevel = 1.0f;

	sf::Vector2f centre((float)this->city.map.width, (float)(this->city.map.height*0.5));
	centre *= float(this->city.map.tileSize);
	gameView.setCenter(centre);

	this->selectionStart = sf::Vector2i(0,0);
	this->selectionEnd = sf::Vector2i(0,0);

	this->currentTile = &this->game->tiles.at("grass");

	this->actionState = ActionState::NONE;
}

void GameStateEditor::draw(const float deltaTime) 
{
	this->game->window.clear(sf::Color::Black);

	this->game->window.setView(this->guiView);
	this->game->window.draw(this->game->background);

	this->game->window.setView(this->gameView);
	city.map.draw(this->game->window, deltaTime);

	this->game->window.setView(this->guiView);
	for (auto GUI : this->guiSystem) {
		this->game->window.draw(GUI.second);
	}

	return;
}

void GameStateEditor::update(const float deltaTime) 
{
	this->city.update(deltaTime);

	this->guiSystem.at("infoBar").setEntryText(0, "Day: " + std::to_string(this->city.day));
	this->guiSystem.at("infoBar").setEntryText(1, "�" + std::to_string(long(this->city.funds)));
	this->guiSystem.at("infoBar").setEntryText(2, "Pop: " + std::to_string(long(this->city.population)) + "(" + std::to_string(long(this->city.getHomeless())) + ")");
	this->guiSystem.at("infoBar").setEntryText(3, "Emp: " + std::to_string(long(this->city.employable)) + "(" + std::to_string(long(this->city.getUnemployed())) + ")");
	this->guiSystem.at("infoBar").setEntryText(4, tileTypeToString(currentTile->tileType));

	this->guiSystem.at("rightClickMenu").highlight(this->guiSystem.at("rightClickMenu").getEntry(this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->guiView)));

	return;
}

void GameStateEditor::handleInput()
{
	sf::Event event;

	sf::Vector2f guiPos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->guiView);
	sf::Vector2f gamePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->gameView);

	while (this->game->window.pollEvent(event)) 
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			game->window.close();
			break;
		case sf::Event::Resized:
			gameView.setSize((float)event.size.width, (float)event.size.height);
			gameView.zoom(zoomLevel);
			guiView.setSize((float)event.size.width, (float)event.size.height);

			this->guiSystem.at("infoBar").setDimensions(sf::Vector2f((float)(event.size.width / this->guiSystem.at("infoBar").entries.size()), 16));
			this->guiSystem.at("infoBar").setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, event.size.height - 16), this->guiView));
			this->guiSystem.at("infoBar").show();

			this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
			this->game->background.setScale(float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
				float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
			break;
		case sf::Event::MouseMoved:
			if (this->actionState == ActionState::PANNING)
			{
				sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(this->game->window) - this->panningAnchor);
				gameView.move(-1.0f * pos * this->zoomLevel);
				panningAnchor = sf::Mouse::getPosition(this->game->window);
			}
			else if (actionState == ActionState::SELECTING)
			{
				selectionEnd.x = gamePos.y / (this->city.map.tileSize) + gamePos.x / (2 * this->city.map.tileSize) - this->city.map.width * 0.5 - 0.5;
				selectionEnd.y = gamePos.y / (this->city.map.tileSize) - gamePos.x / (2 * this->city.map.tileSize) + this->city.map.width * 0.5 + 0.5;

				this->city.map.clearSelected();

				if (this->currentTile->tileType == TileType::GRASS)
				{
					this->city.map.select(selectionStart, selectionEnd, { this->currentTile->tileType, TileType::WATER });
				}
				else
				{
					this->city.map.select(selectionStart, selectionEnd,
					{
						this->currentTile->tileType,    TileType::FOREST,
						TileType::WATER,                TileType::ROAD,
						TileType::RESIDENTIAL,          TileType::COMMERCIAL,
						TileType::INDUSTRIAL
					});
				}
				this->guiSystem.at("selectionCostText").setEntryText(0, "�" + std::to_string(this->currentTile->cost * this->city.map.numSelected));
				if (this->city.funds <= this->city.map.numSelected * this->currentTile->cost)
				{
					this->guiSystem.at("selectionCostText").highlight(0);
				}
				else
				{
					this->guiSystem.at("selectionCostText").highlight(-1);
				}
				this->guiSystem.at("selectionCostText").setPosition(guiPos + sf::Vector2f(16, -16));
				this->guiSystem.at("selectionCostText").show();
			}
			this->guiSystem.at("rightClickMenu").highlight(this->guiSystem.at("rightClickMenu").getEntry(guiPos));
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Middle) 
			{
				this->guiSystem.at("rightClickMenu").hide();
				this->guiSystem.at("selectionCostText").hide();

				if (this->actionState != ActionState::PANNING) 
				{
					this->actionState = ActionState::PANNING;
					this->panningAnchor = sf::Mouse::getPosition(this->game->window);
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Left) 
			{
				if (this->guiSystem.at("rightClickMenu").visible == true) 
				{
					std::string msg = this->guiSystem.at("rightClickMenu").activate(guiPos);
					if (msg != "null") 
					{
						this->currentTile = &this->game->tiles.at(msg);
					}
					this->guiSystem.at("rightClickMenu").hide();
				}
				else 
				{
					if (this->actionState != ActionState::SELECTING)
					{
						this->actionState = ActionState::SELECTING;
					
						selectionStart.x = gamePos.y / (this->city.map.tileSize) + gamePos.x / (2 * this->city.map.tileSize) - this->city.map.width * 0.5 - 0.5;
						selectionStart.y = gamePos.y / (this->city.map.tileSize) - gamePos.x / (2 * this->city.map.tileSize) + this->city.map.width * 0.5 + 0.5;
					}
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				if (this->actionState == ActionState::SELECTING)
				{
					this->actionState = ActionState::NONE;
					this->guiSystem.at("selectionCostText").hide();
					this->city.map.clearSelected();
				}
				else 
				{
					sf::Vector2f pos = guiPos;

					if (pos.x > this->game->window.getSize().x - this->guiSystem.at("rightClickMenu").getSize().x) 
					{
						pos -= sf::Vector2f(this->guiSystem.at("rightClickMenu").getSize().x, 0);
					}
					if (pos.y > this->game->window.getSize().y - this->guiSystem.at("rightClickMenu").getSize().y) 
					{
						pos -= sf::Vector2f(0, this->guiSystem.at("rightClickMenu").getSize().y);
					}
					this->guiSystem.at("rightClickMenu").setPosition(pos);
					this->guiSystem.at("rightClickMenu").show();
				}
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Middle) 
			{
				this->actionState = ActionState::NONE;
			}
			else if (event.mouseButton.button == sf::Mouse::Left) 
			{
				if (this->actionState == ActionState::SELECTING)
				{
					if (this->currentTile != nullptr)
					{
						unsigned int cost = this->currentTile->cost * this->city.map.numSelected;
						if (this->city.funds >= cost) 
						{
							this->city.bulldoze(*this->currentTile);
							this->city.funds -= this->currentTile->cost * this->city.map.numSelected;
							this->city.tileChanged();
						}
					}
					this->guiSystem.at("selectionCostText").hide();
					this->actionState = ActionState::NONE;
					this->city.map.clearSelected();
				}
			}
			break;
		case sf::Event::MouseWheelMoved:
			if (event.mouseWheel.delta < 0) 
			{
				gameView.zoom(2.0f);
				zoomLevel *= 2.0f;
			}
			else 
			{
				gameView.zoom(0.5f);
				zoomLevel *= 0.5f;
			}
			break;
		default:
			break;
		}
	}
	return;
}


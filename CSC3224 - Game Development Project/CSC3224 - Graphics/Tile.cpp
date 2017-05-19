#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(const unsigned int tileSize, const unsigned int height, sf::Texture &texture, const std::vector<Animation> &animations, const TileType tileType, const unsigned int cost, const unsigned int maxPopPerLevel, const unsigned int maxLevels) {
	this->tileType = tileType;
	this->tileVariant = 0;
	this->regions[0] = 0;

	this->cost = cost;
	this->population = 0;
	this->maxPopPerLevel = maxPopPerLevel;
	this->maxLevels = maxLevels;
	this->production = 0;
	this->storedGoods = 0;

	this->sprite.setOrigin(sf::Vector2f(0.0f, tileSize * (height - 1)));
	this->sprite.setTexture(texture);
	this->handler.frameSize = sf::IntRect(0, 0, tileSize * 2, tileSize * height);
	for (auto animation : animations) 
	{
		this->handler.update(0.0f);
	}
	this->handler.update(0.0f);
}

void Tile::draw(sf::RenderWindow &window, float deltaTime) 
{
	this->handler.changeAnimation(this->tileVariant);
	this->handler.update(deltaTime);
	this->sprite.setTextureRect(this->handler.bounds);
	window.draw(this->sprite);
	return;
}

void Tile::update() 
{
	if ((this->tileType == TileType::RESIDENTIAL || this->tileType == TileType::COMMERCIAL || this->tileType == TileType::INDUSTRIAL) && this->population == this->maxPopPerLevel * (this->tileVariant+1) && this->tileVariant < this->maxLevels) {
		if (rand() % int(1e4) < 1e2 / (this->tileVariant + 1)) {
			++this->tileVariant;
		}
		return;
	}
}

string tileTypeToString(TileType type) 
{
	switch (type) {
	default:
	case TileType::VOID:
		return "Void";
	case TileType::GRASS:
		return "Flatten";
	case TileType::FOREST:
		return "Forest";
	case TileType::WATER:
		return "Water";
	case TileType::RESIDENTIAL:
		return "Residential Zone";
	case TileType::COMMERCIAL:
		return "Commercial Zone";
	case TileType::INDUSTRIAL:
		return "Industrial Zone";
	case TileType::ROAD:
		return "Road";
	}
}
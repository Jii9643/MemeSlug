#include "Map.h"

enum bTypes {Grass = 0, Platform};

Map::Map(dArr<Texture> &textures, Vector2f position, Vector2f scale, Vector2u windowBounds, int type)
{
	this->dtMultiplier = 60.f;

	this->textures = &textures;
	this->type = type;
	this->block.setTexture((*this->textures)[this->type]);
	this->block.setScale(scale);
	this->block.setPosition(position);

	this->block.setOrigin(
		this->block.getGlobalBounds().width / 2,
		this->block.getGlobalBounds().height / 2
	);

	this->windowBounds = windowBounds;

}


Map::~Map()
{
}

void Map::collisionUpdate(const float& dt, Vector2f entityPosition)
{

}


void Map::Update(const float &dt, Vector2f entityPosition)
{

}


void Map::Draw(RenderTarget &target)
{
	target.draw(this->block);
}
#include "Tile.h"

 Texture Tile::tileTextures;

Tile::Tile(	IntRect textureRect,Vector2f pos,bool isCollider,bool isDamaging)
 {
	this->sprite.setTexture(Tile::tileTextures);
	this->sprite.setTextureRect(textureRect);
	this->sprite.setPosition(pos);
	
	this->isCollider = isCollider;
	this->isDamaging = isDamaging;
}

Tile::~Tile()
{
}

void Tile::Update()
{
}

void Tile::Draw(RenderTarget &target)
{
target.draw(this->sprite);
}
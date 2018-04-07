#include "Box.h"


Box::Box() {}
Box::Box(Texture* texture)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setPosition(800.0f, 800.0f);
	this->sprite.setScale(0.1f, 0.1f);
	this->boxBounds = sprite.getLocalBounds();
	
}



Box::~Box()
{
}

void Box::Draw (RenderTarget& target)
{
	target.draw(this->sprite);
}

void Box::Update() 
{

}
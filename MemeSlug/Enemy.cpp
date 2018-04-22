#include "Enemy.h"

enum eTypes { SimpleSoldier = 0, General };

Enemy::Enemy(Texture *texture, Vector2u windowBounds, Vector2f position, Vector2f direction, 
	Vector2f scale, int type, int hpMax, int damageMax, int damageMin)
{
	this->texture = texture; 
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(0.3, 0.3); 
	this->sprite.setPosition(position);
	this->direction = direction;

	this->dtMultiplier = 60.0f;

	this->type = type;

	this->hpMax = hpMax; 
	this->hp = this->hpMax;

	this->damageMax = damageMax; 
	this->damageMin = damageMin;
}


Enemy::~Enemy()
{

}

void Enemy::takeDamage(int damage) 
{
	this->hp -= damage;
	if (this->hp <= 0)
		this->hp = 0;
}

void Enemy::Update(const float &dt)
{
	switch (this->type)
	{
	case 0: 
		this->sprite.move(this->direction.x *10.f*dt*this->dtMultiplier, this->direction.y *10.f*dt*this->dtMultiplier);
		
		break; 

	default: 
		
		break;
	}
}

void Enemy::Draw(RenderTarget &target)
{
	target.draw(this->sprite);
}






















#include "Enemy.h"

enum eTypes { SimpleSoldier = 0, Ufo };

Enemy::Enemy(dArr<Texture> &textures, Vector2u windowBounds, Vector2f position, Vector2f direction, 
	Vector2f scale, int type, int hpMax, int damageMax, int damageMin, int playerFollowNr)
{
	this->textures = &textures; 
	this->type = type;
	this->sprite.setTexture((*this->textures)[this->type]);
	this->sprite.setScale(scale); 
	this->sprite.setPosition(position);
	this->direction = direction;

	this->damageTimerMax = 5.0f;
	this->damageTimer = 0;

	this->dtMultiplier = 60.0f;


	this->hpMax = hpMax; 
	this->hp = this->hpMax;

	this->damageMax = damageMax; 
	this->damageMin = damageMin;

	this->playerFollowNr = playerFollowNr;

}


Enemy::~Enemy()
{

}

void Enemy::takeDamage(int damage) 
{
	this->hp -= damage;

	this->damageTimer = this->damageTimerMax;

    if (this->hp <= 0)
	{
		this->hp = 0;
	}
}

void Enemy::Update(const float &dt, Vector2f playerPosition)
{
	Vector2f normalizeDir;

	switch (this->type)
	{
	case SimpleSoldier: 
		
		this->sprite.move(this->direction.x *10.f*dt*this->dtMultiplier, this->direction.y *10.f*dt*this->dtMultiplier);
		
		break; 

	case Ufo: 

		if (this->sprite.getPosition().x > playerPosition.x)
		{
			direction.x = playerPosition.x - this->sprite.getPosition().x; //distanza tra enemy e player
			direction.y = playerPosition.y - this->sprite.getPosition().y;
		}
		normalizeDir = normalize(direction, vectorLength(direction)); //normalizzo quindi tra 0 e 1

		if (normalizeDir.y > 0.3)
			normalizeDir.y = 0.3;
		else if (normalizeDir.y < -0.3)
			normalizeDir.y = -0.3;


		if (normalizeDir.x > -0.7)
			normalizeDir.x = -0.7;

		this->sprite.move(normalizeDir.x * 1.f * dt * this->dtMultiplier, normalizeDir.y * 4.f * dt * this->dtMultiplier);

	default: 
		
		break;
	}

	if (this->damageTimer > 0.0f)
	{
		this->damageTimer -= 1.0f*dt*dtMultiplier;

		this->sprite.setColor(Color::Red);

		this->sprite.move(20.0f*dt*dtMultiplier , 0.0f);
	}
	else
		this->sprite.setColor(Color::White);
}

void Enemy::Draw(RenderTarget &target)
{
	target.draw(this->sprite);
}






















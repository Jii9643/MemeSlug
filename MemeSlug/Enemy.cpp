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

	switch(this->type)
	{
	case SimpleSoldier:
		this->maxVelocity = 10.f;
	    break;
	case Ufo: 
		this->maxVelocity = 5.f;
	    break;
	default: 
		break;
	}
	

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

void Enemy::collisionUpdate(const float& dt)
{
	if (this->damageTimer > 0.0f)
	{

		this->sprite.setColor(Color::Red);

		this->sprite.move(
			this->maxVelocity* -this->normalizeDir.x *  this->damageTimer * dt*dtMultiplier,
			this->maxVelocity* -this->normalizeDir.y *  this->damageTimer * dt*dtMultiplier);
	}
	else
		this->sprite.setColor(Color::White);
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
	

	switch (this->type)
	{
	case SimpleSoldier: 
		
		this->sprite.move(
			this->direction.x *this->maxVelocity*dt*this->dtMultiplier, 
			this->direction.y *this->maxVelocity*dt*this->dtMultiplier);

		this->normalizeDir = normalize(this->direction, vectorLength(this->direction));
		
		break; 

	case Ufo: 

		if (this->sprite.getPosition().x > playerPosition.x)
		{
			this->direction.x = playerPosition.x - this->sprite.getPosition().x; //distanza tra enemy e player
			this->direction.y = playerPosition.y - this->sprite.getPosition().y;
		}
		this->normalizeDir = normalize(this->direction, vectorLength(this->direction)); //normalizzo quindi tra 0 e 1

		if (this->normalizeDir.y > 0.3)
			this->normalizeDir.y = 0.3;
		else if (this->normalizeDir.y < -0.3)
			this->normalizeDir.y = -0.3;


		if (this->normalizeDir.x > -0.7)
			this->normalizeDir.x = -0.7;

		this->sprite.move(
			this->normalizeDir.x * this->maxVelocity * dt * this->dtMultiplier, 
			this->normalizeDir.y * (this->maxVelocity + 15) * dt * this->dtMultiplier);

	default: 
		
		break;
	}

	if (this->damageTimer > 0.0f)
	{
		this->damageTimer -= 1.0f*dt*dtMultiplier;

		this->sprite.setColor(Color::Red);

		this->sprite.move(20.0f* -this->normalizeDir.x *  this->damageTimer * dt*dtMultiplier ,
			              20.0f* -this->normalizeDir.y *  this->damageTimer * dt*dtMultiplier);
	}
	else
		this->sprite.setColor(Color::White);
	
	//Collisione
	this->collisionUpdate(dt);
}

void Enemy::Draw(RenderTarget &target)
{
	target.draw(this->sprite);
}






















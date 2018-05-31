#include "Enemy.h"


enum eTypes { SimpleSoldier = 0, Ufo, AssaultSoldier };
enum bulletTypes { Regular = 0, Missile1
};

Enemy::Enemy(dArr<Texture> &textures, dArr<Texture> &bulletTextures, Vector2u windowBounds, Vector2f position, Vector2f moveDirection,
	 Vector2f scale, int type, int hpMax, int damageMax, int damageMin, int playerFollowNr, StrategyMove* sm)
{

	this->dtMultiplier = 60.0f;

	this->textures = &textures; 
	this->bulletTextures = &bulletTextures;
	this->type = type;
	this->sprite.setTexture((*this->textures)[this->type]);
	this->sprite.setScale(scale);
	this->sprite.setPosition(position);
	this->moveDirection = moveDirection;
	
	this->shootTimerMax = 5.f;
	this->shootTimer = this->shootTimerMax;
	
    this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().height / 2
	);

	this->windowBounds = windowBounds; 

	this->damageTimerMax = 5.0f;
	this->damageTimer = 0;

	this->strategy = sm;
	



	switch(this->type)
	{
	
	case SimpleSoldier:
		this->maxVelocity = 3.f;
	    break;
	
	case Ufo: 
		this->maxVelocity = 5.f;
	    break;

	case AssaultSoldier: 
		this->maxVelocity = 1.f;
		this->shootTimerMax = 5.f;
		this->shootTimer = 0.f;
		break;

	default: 
		break;
	}
	




	this->hpMax = hpMax; 
	this->hp = this->hpMax;

	this->damageMax = damageMax; 
	this->damageMin = damageMin;

	this->playerFollowNr = playerFollowNr;

}


Enemy::~Enemy()
{

}

void Enemy::collisionUpdate(const float& dt, Vector2f playerPosition)
{

	
	if (this->damageTimer > 0.0f)
	{
		
		this->sprite.setColor(Color::Red);
		
		this->sprite.move(
			this->maxVelocity* -this->normalizedMoveDir.x *  this->damageTimer * dt*dtMultiplier,
			this->maxVelocity* -this->normalizedMoveDir.y *  this->damageTimer * dt*dtMultiplier);
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
		
		if (this->sprite.getPosition().x  > playerPosition.x)
		{
			this->sprite.setScale(1.3f, 1.3f);
			strategy = new StrategyL(
				-this->moveDirection.x *this->maxVelocity*dt*this->dtMultiplier,
				this->moveDirection.y *this->maxVelocity*dt*this->dtMultiplier);
			this->sprite.move(strategy->StrategyEnemy());
			delete strategy;
			this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));
		}
		else if (this->sprite.getPosition().x + 100 < playerPosition.x)
		{
			this->sprite.setScale(-1.3f, 1.3f);
			strategy = new StrategyR(
				-this->moveDirection.x *this->maxVelocity*dt*this->dtMultiplier,
				this->moveDirection.y *this->maxVelocity*dt*this->dtMultiplier);
			this->sprite.move(strategy->StrategyEnemy());
			delete strategy;
			this->normalizedMoveDir = normalize(-this->moveDirection, vectorLength(this->moveDirection));
		}
		
		break; 

	case Ufo: 

		if (this->sprite.getPosition().x > playerPosition.x)
		{
			this->moveDirection.x = playerPosition.x - this->sprite.getPosition().x; //distanza tra enemy e player
			this->moveDirection.y = playerPosition.y - this->sprite.getPosition().y;
		}
		
		/*if (this->normalizedMoveDir.y > 0.3)
			this->normalizedMoveDir.y = 0.3;
		else if (this->normalizedMoveDir.y < -0.3)
			this->normalizedMoveDir.y = -0.3;


		if (this->normalizedMoveDir.x > -0.7)
			this->normalizedMoveDir.x = -0.7;*/

		if (this->sprite.getPosition().x   > playerPosition.x)
		{
			strategy = new StrategyL(
				-this->normalizedMoveDir.x * this->maxVelocity  * dt * this->dtMultiplier,
				this->normalizedMoveDir.y * (this->maxVelocity + 15) * dt * this->dtMultiplier);
			this->sprite.move(strategy->StrategyEnemy());
			delete strategy;
			this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));
		}
		else if (this->sprite.getPosition().x  < playerPosition.x)
		{
			strategy = new StrategyR(
				this->moveDirection.x *this->maxVelocity*dt*this->dtMultiplier,
				this->moveDirection.y *this->maxVelocity*dt*this->dtMultiplier);
			this->sprite.move(strategy->StrategyEnemy());
			delete strategy;
			this->normalizedMoveDir = normalize(-this->moveDirection, vectorLength(this->moveDirection));
		}

		/*this->sprite.move(
			this->normalizedMoveDir.x * this->maxVelocity * dt * this->dtMultiplier, 
			this->normalizedMoveDir.y * (this->maxVelocity + 15) * dt * this->dtMultiplier);*/

		break;
	
	case AssaultSoldier:

		this->shootTimerMax = 60.f;

		if (this->shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f *dt * this->dtMultiplier;

		this->lookDirection.x = playerPosition.x - this->sprite.getPosition().x; //distanza tra enemy e player
		this->lookDirection.y = playerPosition.y - this->sprite.getPosition().y;
		
		this->normalizedLookDir = normalize(this->lookDirection, vectorLength(this->lookDirection));

		if (this->sprite.getPosition().x - 200  > playerPosition.x)
		{
			this->sprite.setScale(0.28f, 0.28f);
			strategy = new StrategyL(
				-this->moveDirection.x *this->maxVelocity*dt*this->dtMultiplier,
				this->moveDirection.y *this->maxVelocity*dt*this->dtMultiplier);
			this->sprite.move(strategy->StrategyEnemy());
			delete strategy;
			this->normalizedMoveDir = normalize(this->moveDirection, vectorLength(this->moveDirection));
		}
		else if (this->sprite.getPosition().x + 200 < playerPosition.x)
		{
			this->sprite.setScale(-0.28f, 0.28f);
			strategy = new StrategyR(
				-this->moveDirection.x *this->maxVelocity*dt*this->dtMultiplier,
				this->moveDirection.y *this->maxVelocity*dt*this->dtMultiplier);
			this->sprite.move(strategy->StrategyEnemy());
			delete strategy;
			this->normalizedMoveDir = normalize(-this->moveDirection, vectorLength(this->moveDirection));
		}



		//Sparo
		if (this->shootTimer >= this->shootTimerMax)
		{
			if (this->sprite.getPosition().x > playerPosition.x)
			{
				this->bullets.add(Bullet(&(*this->bulletTextures)[Regular], Vector2f(this->sprite.getPosition().x - 20, this->sprite.getPosition().y + 35),
					Vector2f(-0.15f, 0.15f), Vector2f(-1.f, 0.f),
					2.f, 5.f, 0.5f));
			}
			else if (this->sprite.getPosition().x  < playerPosition.x)
			{
				this->bullets.add(Bullet(&(*this->bulletTextures)[Regular], Vector2f(this->sprite.getPosition().x - 20, this->sprite.getPosition().y + 35),
					Vector2f(0.15f, 0.15f), Vector2f(1.f, 0.f),
					8.f, 13.f, 0.5f));
			}
			this->shootTimer = 0.f;
		}

		break;

	default: 
		
		break;
	}

	if (this->damageTimer > 0.0f)
	{
		this->damageTimer -= 1.0f*dt*dtMultiplier;

		this->sprite.setColor(Color::Red);

		this->sprite.move(20.0f* -this->normalizedMoveDir.x *  this->damageTimer * dt*dtMultiplier ,
			              20.0f* -this->normalizedMoveDir.y *  this->damageTimer * dt*dtMultiplier);
	}
	else
		this->sprite.setColor(Color::White);
	
	//Collisione
	this->collisionUpdate(dt, playerPosition);
}

void Enemy::Draw(RenderTarget &target)
{
	target.draw(this->sprite);

		for (size_t i = 0; i < this->bullets.size(); i++)
		{
			this->bullets[i].Draw(target);
		}
	
}






















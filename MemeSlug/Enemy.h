#pragma once
#include "Bullet.h"
#include "StrategyL.h"
#include"StrategyR.h"
#include"StrategyMove.h"


class Enemy
{
public:
	Enemy(dArr<Texture> &textures, dArr<Texture> &bulletTextures, Vector2u windowBounds, Vector2f position, Vector2f moveDirection,
		Vector2f scale, int type, int hpMax, int damageMax, int damageMin, int playerFollowNr, StrategyMove* sm = nullptr);

	virtual ~Enemy();
	
	//Accessori
	inline const int getDamage() const { return this->damageMin; }
	inline const int getHP() const{ return this->hp;  }
	inline const int getHPMax() const { return this->hpMax;  }
	inline const bool isDead() const { return this->hp <= 0;  }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline Vector2f getPosition() const { return this->sprite.getPosition(); }
	inline const int& getPlayerFollowNr() const { return this->playerFollowNr; }
	inline const int& getType() const { return this->type; }
	inline dArr<Bullet>& getBullets() { return this->bullets; }

	//Funzioni 
	void collisionUpdate(const float& dt,Vector2f playerPosition);
	void takeDamage(int damage);
	void Update(const float &dt, Vector2f playerPosition);
	void Draw(RenderTarget &target);

	//Vettore distanza tra enemy e player (norma)

	float vectorLength(Vector2f v)            
	{
		return sqrt(pow(v.x, 2) + pow(v.y, 2)); 
	}

	Vector2f normalize(Vector2f v, float length)
	{
		if (length == 0)
			return Vector2f(0.f, 0.f);
		else
			return v / length;
	}

private: 
	dArr<Texture> *textures;
	Sprite sprite; 
	Vector2u windowBounds;
	Vector2f lookDirection;
	Vector2f normalizedLookDir;
	Vector2f moveDirection;
	Vector2f normalizedMoveDir;
	float maxVelocity;

	dArr <Texture> *bulletTextures;
	dArr <Bullet> bullets;

	float dtMultiplier;
	float damageTimer;
	float damageTimerMax;

	float shootTimerMax;
	float shootTimer;

	int type;
	int hp; 
	int hpMax; 
	int damageMin; 
	int damageMax;
	int playerFollowNr;

	//Strategy
	StrategyMove* strategy;
};


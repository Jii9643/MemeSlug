#pragma once
#include "Box.h"

class Enemy
{
public:
	Enemy(dArr<Texture> &textures, Vector2u windowBounds,  Vector2f position, Vector2f direction, 
		Vector2f scale, int type, int hpMax, int damageMax, int damageMin, int playerFollowNr);

	virtual ~Enemy();
	
	//Accessori
	inline const int getDamage() const { return this->damageMin; }
	inline const int getHP() const{ return this->hp;  }
	inline const int getHPMax() const { return this->hpMax;  }
	inline const bool isDead() const { return this->hp <= 0;  }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline Vector2f getPosition() const { return this->sprite.getPosition(); }
	inline const int& getPlayerFollowNr() const { return this->playerFollowNr; }

	//Funzioni 
	void collisionUpdate(const float& dt);
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
	Vector2f direction;
	Vector2f normalizeDir;
	float maxVelocity;

	float dtMultiplier;
	float damageTimer;
	float damageTimerMax;

	int type; 
	int hp; 
	int hpMax; 
	int damageMin; 
	int damageMax;
	int playerFollowNr;
};


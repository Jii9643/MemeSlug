#pragma once
#include "Box.h"

class Enemy
{
public:
	Enemy(Texture *texture, Vector2u windowBounds,  Vector2f position, Vector2f direction, Vector2f scale, int type, int hpMax, int damageMax, int damageMin);

	virtual ~Enemy();
	
	//Accessori
	inline const int getDamage() const { return this->damageMin; }
	inline const int getHP() const{ return this->hp;  }
	inline const int getHPMax() const { return this->hpMax;  }
	inline const bool isDead() const { return this->hp <= 0;  }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline Vector2f getPosition() const { return this->sprite.getPosition(); }

	//Funzioni 
	void takeDamage(int damage);
	void Update(const float &dt);
	void Draw(RenderTarget &target);

private: 
	Texture * texture;
	Sprite sprite; 
	Vector2u windowBounds;
	Vector2f direction;

	float dtMultiplier;

	int type; 
	int hp; 
	int hpMax; 
	int damageMin; 
	int damageMax;
};


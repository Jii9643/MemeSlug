#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include "dArr.h"

using namespace sf;


class Pickup
{

public:
	
	Pickup(dArr <Texture>& textures, Vector2f position, Vector2f scale, int type, float duration);
	virtual ~Pickup();

	inline const int& getType() const { return this->type;  }
	inline const bool canDelete() const { return this->aliveTimer >= this->aliveTimerMax; }
	inline Vector2f getPosition() { return this->sprite.getPosition(); }

	bool checkCollision(FloatRect rect);
	void Update(const float& dt);
	void Draw(RenderTarget& target);

private:

	float dtMultiplier;
	int type; 
	dArr<Texture> *textures;
	Sprite sprite;
	float aliveTimerMax; 
	float aliveTimer;

};


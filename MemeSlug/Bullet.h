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

class Bullet
{
public:
	
	Bullet(Texture *texture, Vector2f position, Vector2f scale,
		 Vector2f direction, float initialVelocity, float maxVelocity, float acceleration);
	virtual ~Bullet();
	
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }

	void Movement(const float &dt);
    void Update(const float &dt);
	void Draw(RenderTarget &target);

private:
    
	float dtMultiplier;

	Texture * texture;
	Sprite sprite;


	Vector2f currentVelocity;
	float initialVelocity;
	float maxVelocity;
	float acceleration;
	Vector2f direction;
};

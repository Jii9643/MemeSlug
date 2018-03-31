#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <vector>

using namespace sf;

class Bullet
{
public:
	Bullet(Texture *texture, Vector2f position, Vector2f maxVelocity = Vector2f (15.0f, 0.0f));
	virtual ~Bullet();

	void Movement();
	
	void Update();
	void Draw(RenderTarget &target);

private:
	Texture *texture;
	Sprite sprite;

	Vector2f maxVelocity;
};


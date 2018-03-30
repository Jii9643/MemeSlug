#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML\System.hpp>
#include <iostream>

using namespace sf;

class Player
{
public:

	Player(Texture *texture, int UP = 73, int DOWN = 74, int LEFT = 71, int RIGHT = 72, int SHOOT= 0, int JUMP= 57);
	virtual ~Player();

	void Draw(RenderTarget &target);
	void Update();
	void Movement();

private:

	Texture *texture;
	Sprite sprite;
	RectangleShape hitBox;

	int controls[6];

	int score;
	int hp;
	int damage;
};


#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class StrategyMove
{
public:
	StrategyMove(float x, float y) : moveX(x), moveY(y) {}

	virtual Vector2f StrategyEnemy() = 0;

protected: 

	float moveX;
	float moveY;
};
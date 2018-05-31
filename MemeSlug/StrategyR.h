#pragma once

#include"StrategyMove.h"

using namespace sf;

class StrategyR : public StrategyMove
{
public:
	StrategyR(float moveX,float moveY) : StrategyMove (moveX, moveY){}

	Vector2f StrategyEnemy() override
	{
		Vector2f movement;
		movement.x = moveX;
		movement.y = moveY;
		return movement;
	}
};
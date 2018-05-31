#pragma once

#include"StrategyMove.h"


class StrategyL : public StrategyMove
{
public:
	StrategyL(float moveX, float moveY) : StrategyMove(moveX, moveY) {}

	Vector2f StrategyEnemy() override
	{
		Vector2f movement;
		movement.x = -moveX;
		movement.y = moveY;
		return movement;
	}
};
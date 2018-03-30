#pragma once
#include "Player.h"


class Game
{
public:
	Game(RenderWindow *window);
	virtual ~Game();
	//Accessors
	inline RenderWindow& getwindow() 
	{ return *this->window; }

	//Functions
	void Update();
	void Draw();

private:
	RenderWindow *window;

	Player *player;
	Texture playerTexture;
};


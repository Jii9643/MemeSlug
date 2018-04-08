#pragma once
#include "Player.h"


class Game
{
public:

	Game(RenderWindow *window);
	virtual ~Game();
	//Accessors
	inline RenderWindow& getwindow()
	{
		return *this->window;
	}

	//Functions
	void Update();
	void Draw();
	void UpdateUI();
	void InitUI();
	void DrawUI();

private:
	RenderWindow * window;

	//Text
	Font font;
	std::vector<Text> staticPlayerTexts;

	//Players
	std::vector<Player> players;
	std::vector<Box> boxes;

	//Textures
	Texture playerTexture;
	Texture bulletTexture;
	Texture boxTexture;
};
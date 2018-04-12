#pragma once
#include "Player.h"


class Game
{
public:

	Game(RenderWindow *window);
	virtual ~Game();
	
	//Accessore alla window
	inline RenderWindow& getwindow()
	{
		return *this->window;
	}

	//Funzioni 
	void Update();
	void Draw();

	//Funzioni per l'interfaccia utente (ancora non implementate)
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
	std::vector<Texture> textures;
	Texture boxTexture;
};
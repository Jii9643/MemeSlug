#pragma once
#include "Player.h"
#include "Enemy.h"

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
	bool runGame;

	//Text
	Font font;
	std::vector<Text> staticPlayerTexts;
	Text gameOverText;

	//Players
	std::vector<Player> players;
	int playersAlive;

	//Boxes.
	std::vector<Box> boxes;

	//Enemies
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	int enemySpawnTimer;
	int enemySpawnTimerMax;

	//Textures
	std::vector<Texture> textures;
	Texture boxTexture;
};
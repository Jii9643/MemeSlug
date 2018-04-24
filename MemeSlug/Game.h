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
	void Update(const float &dt);
	void Draw();

	//Funzioni per l'interfaccia utente (ancora non implementate)
	void UpdateUI();
	void InitUI();
	void DrawUI();

private:

	RenderWindow * window;
	bool runGame;
	float dtMultiplier;

	//Text
	Font font;
	Text staticPlayerText;
	Text gameOverText;

	//Players
	dArr<Player> players;
	

	//Boxes.
	std::vector<Box> boxes;

	//Enemies
	dArr<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;

	//Textures
	std::vector<Texture> textures;
	Texture boxTexture;
};
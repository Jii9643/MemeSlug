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
	void InitTextures();

	//Funzioni per l'interfaccia utente (ancora non implementate)
	void UpdateUI();
	void InitUI();
	void DrawUI();

private:

	RenderWindow * window;
	bool runGame;
	float dtMultiplier;

	//Score
	unsigned score;
	unsigned scoreMultiplier;
	float multiplierTimerMax;
	float multiplierTimer;
	int multiplierAdder;
	int multiplierAdderMax;

	//Text
	Font font;
	Text staticPlayerText;
	Text gameOverText;
	Text scoreText;

	//Players
	dArr<Player> players;

	//Pickups
	dArr<Pickup> pickups;

	//Enemies
	dArr<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;

	//Textures
	std::vector<Texture> textures;
	dArr <Texture> enemyTextures;
	Texture boxTexture;
	dArr <Texture> enemyBulletTextures;
	dArr<Texture> pickupTextures;
};
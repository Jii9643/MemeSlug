#pragma once
#include "Player.h"
#include "Enemy.h"
#include"Boss.h"
#include "Achievement.h"
#include "Map.h"





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
	void Draw(const float dt);
	void InitTextures();

	//Funzioni Mappa
	void InitMap();
	void CreateMap();


	//Funzioni per l'interfaccia utente (ancora non implementate)
	void UpdateUI();
	void InitUI();
	void DrawUI();

	void initView();

private:

	RenderWindow * window;
	bool runGame;
	float dtMultiplier;
	float keyTime;
	float keyTimeMax;
	bool paused;

	View mainView;

	//Score
	Clock scoreTimer;
    int scoreTime;
	unsigned score;
	unsigned scoreMultiplier;
	float multiplierTimerMax;
	float multiplierTimer;
	int multiplierAdder;
	int multiplierAdderMax;

	//Text
	Font font;
	Font font1;
	Text staticPlayerText;
	Text gameOverText;
	Text scoreText;
	Text controlsText;

	//Achievemnts texts
	Text killSoldierText;
	Text killUfoText;
	Text pointsText;
	float AchievementTimer;
	float AchievementTimerMax;
	int soldierKilled; 
	int ufoKilled;
	

	//Players
	dArr<Player> players;

	//Bosses
	bool bossEncounter;
	dArr<Boss> bosses;

	//Pickups
	dArr<Pickup> pickups;

	//Enemies
	dArr<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int enemiesAlive;

	//Achievements
     std::vector <Achievements> achievements;

	 //Strategy
	 StrategyMove* move;
	
	//Map
	 dArr <Map> blocks;
	

	//Textures
	std::vector<Texture> textures;

	//Enemy textures
	dArr <Texture> enemyTextures;
	dArr <Texture> enemyBulletTextures;

	//Pickup textures
	dArr<Texture> pickupTextures;

	//Boss textures
	dArr<Texture> bossBodyTextures;
	dArr<Texture> bossGunTextures;
	dArr<Texture> bossBulletTextures;

	//Map Textures
	dArr <Texture> mapTextures;

	//Background
	Sprite backgroundSprite; 
	Texture backgroundTexture;

	

	

};
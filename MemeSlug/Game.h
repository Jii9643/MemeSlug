#pragma once
#include "Player.h"
#include "Enemy.h"
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


	//Funzioni per l'interfaccia utente 
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
	bool endGame;

	View mainView;
	const float LeftScreenBounds = -300.f;
	const float RightScreenBounds = 15000.f;


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
	Text endGameText;

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

	

	//Pickups
	dArr<Pickup> pickups;

	//Enemies
	dArr<Enemy> enemies;
	std::vector<Enemy> enemiesSaved;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int enemiesAlive;
	bool bossIsAlive;

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

	
	//Map Textures
	dArr <Texture> mapTextures;

	//Background
	Sprite backgroundSprite; 
	Texture backgroundTexture;
	Sprite backgroundSprite1;
	Texture backgroundTexture1;
	Sprite backgroundSprite2;
	Texture backgroundTexture2;
	Sprite EndSprite;
	Texture EndTexture;

	

	

};
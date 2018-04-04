#pragma once
#include"Bullet.h"

class Player
{
public:

	Player(Texture *texture, Texture *bulletTexture, int UP = 73, int DOWN = 74, int LEFT = 71, int RIGHT = 72, int SHOOT = 0, int JUMP = 57);
	virtual ~Player();

	inline std::vector<Bullet>& getBullets() { return this->bullets; }

	void Draw(RenderTarget &target);
	void Update();
	void Movement();
	void Combat();


	//Membri statici
	static unsigned players;
	


private:

	Texture * texture;
	Sprite sprite;
	RectangleShape hitBox;

	unsigned playerNr;
	int shootTimer;
	int shootTimerMax;
	int damageTimer;
	int damageTimerMax;

	Texture *bulletTexture;
	std::vector<Bullet> bullets;

	int controls[6];

	int score;
	int hp;
	int damage;
};
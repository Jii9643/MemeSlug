#pragma once
#include"Bullet.h"

class Player : public Box
{
public:

	Player(Texture *texture, Texture *bulletTexture);
	virtual ~Player();

	inline std::vector<Bullet>& getBullets() { return this->bullets; }

	void Draw(RenderTarget &target);
	void Update();
	void Movement();
	void Combat();

	FloatRect playerBounds;

	//Membri statici
	static unsigned players;

private:
	Texture * texture;
	Sprite sprite;
	RectangleShape hitBox;
	Texture * bulletTexture;
	std::vector<Bullet> bullets;

	Vector2f velocity;
	float jumpHeight;
	int speed;
	bool isJumping;

	const float ground = 700.0f;
	const float gravitySpeed = 10.0;

	bool faceRight;
	unsigned playerNr;
	int shootTimer;
	int shootTimerMax;
	int damageTimer;
	int damageTimerMax;



	int controls[4];

	int score;
	int hp;
	int damage;
};
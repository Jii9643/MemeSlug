#pragma once
#include"Bullet.h"

class Player
{

public:

	Player(std::vector<Texture> &textures);
	virtual ~Player();

	//Funzione inline, riferimento a bullets.
	inline std::vector<Bullet>& getBullets() { return this->bullets; }

	//Funzione inline, riferimento a posizione di player.
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }
	inline const int getDamage() const { return this->damage; }
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline const int& getHp() const { return this->hp; }
	inline const int& getHpMax() const { return this->hpMax; }
	inline void takeDamage(int damage) { this->hp -= damage; }
	inline bool isAlive() const {return this->hp > 0;}


	//Funzioni 
	void Draw(RenderTarget &target);
	void Update();
	void Movement();
	void Combat();

	FloatRect playerBounds;

	//Membri statici
	static unsigned players;

private:
	
	//Membri riguardanti player.
	Sprite sprite;
	RectangleShape hitBox;
	Vector2f playerCenter;
	Vector2f direction;
	Vector2f currentVelocity;

	bool faceRight;
	
    float maxVelocity;
	float acceleration;
	float jumpHeight;
	int speed;
	float stabilizerForce;
	
	unsigned playerNr;

	//Puntatori a texture per i diversi tipi di bullet.
	Texture *bulletTexture;
	Texture *missileTexture;
	std::vector<Bullet> bullets;
	
	//Attributi mappa. (temporanei)
    const float ground = 700.0f;
	const float gravitySpeed = 5.0;

	//Timing riguardante il rate dei bullets.
	int shootTimer;
	int shootTimerMax;
	int damageTimer;
	int damageTimerMax;

	int jumpTimer; 
	int jumpTimerMax;

	//UI interface (ancora da implementare).
	int score;
	int hp;
	int hpMax;
	int damage;

	//Membro che indica l'arma corrente.
	int currentWeapon;

};
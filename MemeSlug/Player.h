#pragma once
#include"Bullet.h"

class Player
{

public:

	float dtMultiplier;

	Player(std::vector<Texture> &textures);
	virtual ~Player();

	//Bullets del player.
	Bullet& getBullet(unsigned index);
	void removeBullet(unsigned index);
	inline const int getBulletsSize() const { return this->bullets.size(); }

	//Funzioni inline
	inline const Vector2f& getPosition() const { return this->sprite.getPosition(); }
	int getDamage() const;
	inline FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
	inline const int& getHp() const { return this->hp; }
	inline const int& getHpMax() const { return this->hpMax; }
	void takeDamage(int damage);
	inline bool isAlive() const { return this->hp > 0; }
	inline void gainScore(int score) { this->score += score; }
	inline const int getScore() { return this->score; }
	inline bool isDamagedCooldown() { return this->damageTimer < this->damageTimerMax; }
	inline void enableMissile() { this->currentWeapon = 1; }
	inline void disableMissile() { this->currentWeapon = 0; }
	inline void enableLaser() { this->currentWeapon = 2; }
	inline void disableLaser() { this->currentWeapon = 0; }
	inline void enablePiercingShot() { this->piercingShot = true; }
	inline void disablePiercingShot() { this->piercingShot = false; }
	inline bool getPiercingShot() const { return this->piercingShot; }


	//Funzioni 
	void Reset();
	void Draw(RenderTarget &target);
	void Update(Vector2u windowBounds, const float &dt);
	void Movement(Vector2u windowBounds,const float &dt);
	void Combat(const float &dt);

	FloatRect playerBounds;

	//Membri statici
	static unsigned players;

	//Funzioni regolari
	float vectorLength(Vector2f v)
	{
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}

	Vector2f normalize(Vector2f v, float length)
	{
		if (length == 0)
			return Vector2f(0.f, 0.f);
		else
		return v / length;
	}


private:
	
	//Membri riguardanti player.
	Sprite sprite;
	RectangleShape hitBox;
	Vector2f playerCenter;
	Vector2f direction;
	Vector2f currentVelocity;

	bool faceRight;

	//Pickups
	bool piercingShot;


    float maxVelocity;
	float acceleration;
	float jumpHeight;
	int speed;
	float stabilizerForce;
	Vector2f movementDirection;
	Vector2f normDir;
	
	unsigned playerNr;

	//Puntatori a texture per i diversi tipi di bullet.
	Texture *bulletTexture;
	Texture *missileTexture;
	Texture *laserTexture;
	dArr<Bullet> bullets;
	
	//Attributi mappa. (temporanei)
    const float ground = 700.0f;
	const float gravitySpeed = 10.0;

	//Timing riguardante il rate dei bullets.
	float shootTimer;
	float shootTimerMax;
	float damageTimer;
	float damageTimerMax;

	float jumpTimer; 
	float jumpTimerMax;



	//UI interface (ancora da implementare).
	int score;
	int hp;
	int hpMax;
	int damage;

	//Membro che indica l'arma corrente.
	int currentWeapon;

};
#pragma once
#include "Achievement.h"
#include"Bullet.h"
#include"Subject.h"
#include <list>

class Player : public Subject
{

public:

	float dtMultiplier;

	Player(std::vector<Texture> &textures, int ks, int ku, int pnts);
	virtual ~Player();

	//Bullets del player.
	Bullet& getBullet(unsigned index);
	void removeBullet(unsigned index);
	inline const int getBulletsSize() const { return this->bullets.size(); }

	//Funzioni inline
	inline const float& getPositionX() const { return this->sprite.getPosition().x; }
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
	inline const Vector2f& getNormDir()const { return this->normDir; }
	inline void move(float x, float y) { this->sprite.move(x, y);}
	inline const Vector2f& getCurrentVelocity() {return this->currentVelocity; }
	
	//Funzioni 
	void Reset();
	void Draw(RenderTarget &target);
	void Update(Vector2u windowBounds, const float &dt);
	void Movement(Vector2u windowBounds,const float &dt);
	void Combat(const float &dt);

	//Funzioni Achievements
	virtual void Notify()const;
	virtual void Attach(Observer*o)override;
	virtual void Detach(Observer*o)override;
	void Changed() { Notify(); };
	void SetKillSoldier();
	void SetKillUfo();
	void SetPoints(int pnts);
    
	void blockCollision(Vector2f blockPosition, const float &dt);

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
	

	//Observer 
	std::list<Observer*>observer;
	int killSoldier;
	int killUfo;
	int points;
	
	//Attributi mappa. (temporanei)
    const float ground = 600.0f;
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
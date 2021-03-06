#pragma once
#include "Bullet.h"

class Boss
{
public:
	
	Boss(dArr<Texture> &bodyTextures,
		dArr<Texture> &gunTextures,
		dArr<Texture> &bulletTextures,
		Vector2f position, int type);
	virtual ~Boss();

	void Movement();
	void Update(const float& dt); 
	void Draw(RenderTarget& target);

private:

	class BossGun
	{
	public:
		BossGun(Texture *texture,
			Vector2f position,
			float shootTimerMax)
		{
			this->shootTimerMax = shootTimerMax;
			this->shootTimer = this->shootTimerMax;


			this->gunSprite.setTexture(*texture);
			this->gunSprite.setPosition(position);
		}
	
		~BossGun()
		{

		}

		void Update(const float &dt)
		{

		}

		void Draw(RenderTarget &target)
		{
			target.draw(this->gunSprite);
		}

	private:
		float dtMultiplier;

		Sprite gunSprite;

		float shootTimerMax;
		float shootTimer;


	};

	int type; 
	int nrOfGuns;
	float dtMultiplier;


	dArr<Texture>* bodyTextures; 
	dArr<Texture>* gunTextures;
	dArr<Texture>* bulletTextures;
	Sprite sprite;
	dArr<BossGun> guns; 
	dArr<Bullet> bullets;

	int damageMax; 
	int damageMin;
	int hpMax; 
	int hp; 

	int damageTimer;
	
};


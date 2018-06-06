#include "Boss.h"

enum textures{BODY = 0};

// 0 : BODY, 1 : Regular gun, 2: Regular bullet


Boss::Boss(dArr<Texture> &bodyTextures,
	dArr<Texture> &gunTextures,
	dArr<Texture> &bulletTextures,
	Vector2f position, int type)
{
	this->type = type; 
	this->bodyTextures = &bodyTextures;
	this->gunTextures = &gunTextures;
	this->bulletTextures = &bulletTextures;


	switch (this->type)
	{
	case 0: 

		
		
			this->sprite.setTexture((*this->bodyTextures)[0]);

		
			this->guns.add(BossGun(&(*this->gunTextures)[0], Vector2f(0.f, 0.f), 20.f));
			this->guns.add(BossGun(&(*this->gunTextures)[0], Vector2f(0.f, 0.f), 20.f));
			this->guns.add(BossGun(&(*this->gunTextures)[0], Vector2f(0.f, 0.f), 20.f));
			
		
		
		this->sprite.setPosition(position);


		
		break;

	case 1: 

		break; 

	default: 

		break;
	}

	
}


Boss::~Boss()
{
}




void Boss::Movement()
{

}



void Boss::Update(const float& dt)
{
	for (size_t i = 0; i < this->guns.size(); i++)
	{
		this->guns[i].Update(dt);
	}

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Update(dt);
	}
}



void Boss::Draw(RenderTarget& target)
{
	target.draw(this->sprite);

	for (size_t i = 0; i < this->guns.size(); i++)
	{
		this->guns[i].Draw(target);
	}

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}
}
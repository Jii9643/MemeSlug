#include "Player.h"

unsigned Player::players = 0;



Player::Player(Texture *texture, Texture *bulletTexture)
	: hp(1), damage(1), score(0), jumpHeight(1)
{
	//Gestione salto
	this->jumpHeight = jumpHeight;

	//Gestione Texture
	this->texture = texture;
	this->bulletTexture = bulletTexture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(0.3f, 0.3f);
	this->sprite.setPosition(100.0f, 700.0f);
	faceRight = true;

	//Gestione frequenza Sparo
	this->shootTimerMax = 20;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 10;
	this->damageTimer = this->damageTimerMax;

	
	//Numero giocatori
	this->playerNr = Player::players;
	Player::players++;

   

}



Player::~Player()
{
}

void Player::Movement()
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		faceRight = false;
		this->sprite.move(-10.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		faceRight = true;
		this->sprite.move(10.0f, 0.0f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && canJump)
	{
		
		canJump = false;
		this->sprite.move(0.0f, -sqrt(2.0f *981.0f*jumpHeight));
		this->sprite.move(0.0f, gravitySpeed);
	}
	
	
	if (sprite.getPosition().y < ground )
	{
		timeInAir = 0.0f;
		this->sprite.move(0.0f, gravitySpeed);
	}
	canJump = true;
	

}

void Player::Draw(RenderTarget &target)
{

	target.draw(this->sprite);

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}

}

void Player::Combat()
{
	if (Keyboard::isKeyPressed(Keyboard::A) && this->shootTimer >= this->shootTimerMax)
	{
		this->bullets.push_back(Bullet(bulletTexture, this->sprite.getPosition()));

		this->shootTimer = 0;
	}
}

void Player::Update()
{
	

	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer++;

	if (this->damageTimer < this->damageTimerMax)
		this->damageTimer++;


	this->Movement();
	this->Combat();

}
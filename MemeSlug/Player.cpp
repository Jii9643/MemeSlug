#include "Player.h"

unsigned Player::players = 0;



Player::Player(Texture *texture, Texture *bulletTexture)
	: hp(1), damage(1), score(0), jumpHeight(1), isJumping(false)
{
	//Gestione salto
	this->jumpHeight = jumpHeight;

	//Gestione Texture
	this->texture = texture;
	this->bulletTexture = bulletTexture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(0.3f, 0.3f);
	this->sprite.setPosition(100.0f, 700.0f);
	this->playerBounds = this->sprite.getLocalBounds();
	faceRight = true;

	//Gestione frequenza Sparo
	this->shootTimerMax = 20;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 10;
	this->damageTimer = this->damageTimerMax;


	this->maxVelocity = 15.0f;
	this->acceleration = 1.0f;

	//Numero giocatori
	this->playerNr = Player::players;
	Player::players++;



}



Player::~Player()
{
}

void Player::Movement()
{
	Vector2f direction;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		faceRight = false;
		this->direction.x = -1.0f;
		this->direction.y = 0.0f;

		if(this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
		   this->currentVelocity.x += this->direction.x * this->acceleration;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		faceRight = true;
		this->direction.x = 1.0f;
		this->direction.y = 0.0f;

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) && isJumping == false)
	{
        isJumping = true;
		this->sprite.move(0.0f, -sqrt(2.0f *981.0f*jumpHeight));
		this->sprite.move(0.0f, gravitySpeed);
	}


	if (this->sprite.getPosition().y < ground )
	{
		this->sprite.move(0.0f, gravitySpeed);
	}
	isJumping = false;

	//Movimento Finale
	this->sprite.move(this->currentVelocity.x, this->currentVelocity.y);


}


void Player::Draw(RenderTarget &target)
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}

	target.draw(this->sprite);

}

void Player::Combat()
{
	if (Keyboard::isKeyPressed(Keyboard::A) && this->shootTimer >= this->shootTimerMax)
	{
		this->bullets.push_back(Bullet(bulletTexture, this->playerCenter, 25.0f, Vector2f(1.0f, 0.0f), 5.0f, 8.0f));

		this->shootTimer = 0;
	}
}

void Player::Update()
{

	
	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer++;

	if (this->damageTimer < this->damageTimerMax)
		this->damageTimer++;

	this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;


	this->Movement();
	this->Combat();


}
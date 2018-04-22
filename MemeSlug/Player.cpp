#include "Player.h"

unsigned Player::players = 0;

//Tipi di arma (temporaneo)
enum weapons{BULLET1 = 0, MISSILE};


Player::Player(std::vector<Texture> &textures)
	: hpMax(5), damage(1), score(0), jumpHeight(1), isJumping(false)
{
	this->isJumping = false;
	this->jumpHeight = jumpHeight;
	this->faceRight = true;

	//Inizializzazione texture del player.
    this->sprite.setTexture(textures[0]);
	this->sprite.setScale(0.119f, 0.119f);
	this->sprite.setPosition(100.0f, 700.0f);
	this->playerBounds = this->sprite.getLocalBounds();
	this->hp = this->hpMax;

	//Inizializzazione delle textures dei bullets.
	this->bulletTexture = &textures[1];
	this->bulletTexture = &textures[2];

	//Gestione frequenza Sparo
	this->shootTimerMax = 20;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 10;
	this->damageTimer = this->damageTimerMax;

	//Velocità, accelerazione e attrito. 
	this->maxVelocity = 15.0f;
	this->acceleration = 1.0f;
	this->stabilizerForce = 0.5f;

	//Arma corrente.
	this->currentWeapon = BULLET1;

	//Numero giocatori
	this->playerNr = Player::players;
	Player::players++;



}



Player::~Player()
{
}

//Metodo di movimento del player. 
void Player::Movement()
{
	Vector2f direction;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		faceRight = false;
		this->direction.x = -1.0f;
		this->direction.y = 0.0f;
		//Per fare il flip della sprite.
		this->sprite.setScale(-0.119f, 0.119f);


		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		faceRight = true;
		this->direction.x = 1.0f;
		this->direction.y = 0.0f;
		this->sprite.setScale(0.119f, 0.119f);

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;

	}

	if (Keyboard::isKeyPressed(Keyboard::Up) && isJumping == false)
	{
		isJumping = true;
		this->sprite.move(0.0f, -sqrt(2.0f *981.0f*jumpHeight));
		this->sprite.move(0.0f, gravitySpeed);
	}


	if (this->sprite.getPosition().y < ground)
	{
		this->sprite.move(0.0f, gravitySpeed);
	}
	isJumping = false;


	//Attrito.
	if (this->currentVelocity.x > 0)
	{
		this->currentVelocity.x -= this->stabilizerForce;

		if (this->currentVelocity.x < 0)
			this->currentVelocity.x = 0;
	}
	else if (this->currentVelocity.x < 0)
	{
		this->currentVelocity.x += this->stabilizerForce;

		if (this->currentVelocity.x > 0)
			this->currentVelocity.x = 0;
	}

	if (this->currentVelocity.y > 0)
	{
		this->currentVelocity.y -= this->stabilizerForce;

		if (this->currentVelocity.y < 0)
			this->currentVelocity.y = 0;
	}
	else if (this->currentVelocity.y < 0)
	{
		this->currentVelocity.y += this->stabilizerForce;

		if (this->currentVelocity.y > 0)
			this->currentVelocity.y = 0;
	}

	//Movimento Finale
	this->sprite.move(this->currentVelocity.x, this->currentVelocity.y);

	//Update del player
	this->playerCenter.x = this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2;


}

//Draw dei bullets.
void Player::Draw(RenderTarget &target)
{
    for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}
    target.draw(this->sprite);
}

//Metodo riguardante l'attacco del fucile del player (da aggiungere la granata)
void Player::Combat()
{
	if (Keyboard::isKeyPressed(Keyboard::A) && this->shootTimer >= this->shootTimerMax)
	{
		if (faceRight == true)
		{
			if (this->currentWeapon == BULLET1)
			{
				//crea i proiettili
				this->bullets.push_back(Bullet(bulletTexture, this->playerCenter,
					Vector2f(0.3f, 0.3f),
					30.0f, Vector2f(1.0f, 0.0f), 1.0f, 2.0f));
			}
			else if (this->currentWeapon == MISSILE)
			{
				//crea i missili
				this->bullets.push_back(Bullet(missileTexture, this->playerCenter,
					Vector2f(0.2f, 0.2f),
					25.0f, Vector2f(1.0f, 0.0f), 5.0f, 8.0f));
			}

		}
		else 
		{
			if (this->currentWeapon == BULLET1)
			{
				//crea i proiettili
				this->bullets.push_back(Bullet(bulletTexture, Vector2f(this->playerCenter.x -80,this->playerCenter.y),
					Vector2f(-0.3f, 0.3f),
					30.0f, Vector2f(-1.0f, 0.0f), 1.0f, 2.0f));
				
			}
			else if (this->currentWeapon == MISSILE)
			{
				//crea i missili
				this->bullets.push_back(Bullet(missileTexture, this->playerCenter,
					Vector2f(0.2f, 0.2f),
					25.0f, Vector2f(-1.0f, 0.0f), 5.0f, 8.0f));
			}
		}
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
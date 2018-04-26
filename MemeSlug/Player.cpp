#include "Player.h"

unsigned Player::players = 0;

//Tipi di arma (temporaneo)
enum weapons{BULLET1 = 0, MISSILE};


Player::Player(std::vector<Texture> &textures)
	: hpMax(5), damage(1), score(0), jumpHeight(40)
{
	
	this->dtMultiplier = 60.f;

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
	this->missileTexture = &textures[2];

	//Gestione frequenza Sparo
	this->shootTimerMax = 20;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 40;
	this->damageTimer = this->damageTimerMax;

	//Frequenza salto.
	this->jumpTimerMax = 65;
	this->jumpTimer = this->jumpTimerMax;

	//Velocità, accelerazione e attrito. 
	this->maxVelocity = 15.0f;
	this->acceleration = 1.0f;
	this->stabilizerForce = 0.5f;

	//Arma corrente.
	this->currentWeapon = MISSILE;

	//Numero giocatori
	this->playerNr = Player::players;
	Player::players++;



}



Player::~Player()
{
}

int Player::getDamage() const 
{
	int damage = 0;

	switch (this->currentWeapon)
	{
	case BULLET1:

		damage = 1;
		
		break;
	
	case MISSILE:

		damage = 2;
		
		break;
	
	default:

		damage = 1;
		
		break;
	}

	return damage;

}

void Player::takeDamage(int damage)
{
	this->hp -= damage;

	this->damageTimer = 0;
}

//Metodo di movimento del player. 
void Player::Movement(const float &dt)
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
			this->currentVelocity.x += this->direction.x * this->acceleration * dt * this->dtMultiplier;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		faceRight = true;
		this->direction.x = 1.0f;
		this->direction.y = 0.0f;
		this->sprite.setScale(0.119f, 0.119f);

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration * dt * this->dtMultiplier;

	}
	
	if (Keyboard::isKeyPressed(Keyboard::Up) && this->jumpTimer >= this->jumpTimerMax)
	{

	 this->direction.x = 0.0f;
	 this->direction.y = -25.0f;


    	if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
		{
			this->currentVelocity.y += this->direction.y * this->acceleration;

		}

		this->jumpTimer = 0;
		
	}
	

	if (this->sprite.getPosition().y < ground)
	{
		this->sprite.move(0.0f, gravitySpeed);
	}
	


	

	//Attrito.
	if (this->currentVelocity.x > 0)
	{
		this->currentVelocity.x -= this->stabilizerForce* dt * this->dtMultiplier;

		if (this->currentVelocity.x < 0)
			this->currentVelocity.x = 0;
	}
	else if (this->currentVelocity.x < 0)
	{
		this->currentVelocity.x += this->stabilizerForce* dt * this->dtMultiplier;

		if (this->currentVelocity.x > 0)
			this->currentVelocity.x = 0;
	}

	if (this->currentVelocity.y > 0)
	{
		this->currentVelocity.y -= this->stabilizerForce* dt * this->dtMultiplier;

		if (this->currentVelocity.y < 0)
			this->currentVelocity.y = 0;
	}
	else if (this->currentVelocity.y < 0)
	{
		this->currentVelocity.y += this->stabilizerForce* dt * this->dtMultiplier;

		if (this->currentVelocity.y > 0)
			this->currentVelocity.y = 0;
	}

	//Movimento Finale
	this->sprite.move(this->currentVelocity.x* dt * this->dtMultiplier, this->currentVelocity.y* dt * this->dtMultiplier);

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
void Player::Combat(const float &dt)
{
	if (Keyboard::isKeyPressed(Keyboard::A) && this->shootTimer >= this->shootTimerMax)
	{
		if (faceRight == true)
		{
			if (this->currentWeapon == BULLET1)
			{
				//crea i proiettili
				this->bullets.add(Bullet(bulletTexture, this->playerCenter,
					Vector2f(0.05f, 0.05f),
					30.0f, Vector2f(1.0f, 0.0f), 1.0f, 2.0f));
			}
			else if (this->currentWeapon == MISSILE)
			{
				//crea i missili
				this->bullets.add(Bullet(missileTexture, this->playerCenter,
					Vector2f(0.3f, 0.3f),
					30.0f, Vector2f(2.0f, 0.0f), 0.08f, 2.0f));
			}

		}
		else 
		{
			if (this->currentWeapon == BULLET1)
			{
				//crea i proiettili
				this->bullets.add(Bullet(bulletTexture, Vector2f(this->playerCenter.x - 140,this->playerCenter.y),
					Vector2f(-0.05f, 0.05f),
					30.0f, Vector2f(-1.0f, 0.0f), 1.0f, 2.0f));
				
			}
			else if (this->currentWeapon == MISSILE)
			{
				//crea i missili
				this->bullets.add(Bullet(missileTexture, Vector2f(this->playerCenter.x - 50, this->playerCenter.y),
					Vector2f(-0.3f, 0.3f),
					30.0f, Vector2f(-2.0f, 0.0f), 0.08f, 2.0f));
			}
		}
		this->shootTimer = 0;
	}

	//Danneggiato
	if (this->isDamagedCooldown())
	{
		if ((int)this->damageTimer % 2 == 0)
		{
			this->sprite.setColor(Color::Magenta);
		}
		else
		{
			this->sprite.setColor(Color::White);
		}
	}
	else
	{
		this->sprite.setColor(Color::White);
	}
}

Bullet& Player::getBullet(unsigned index)
{
	if (index < 0 || index > this->bullets.size())
		throw ("OUT OF BOUNDS! PLAYER::GETBULLET!");
	
	return this->bullets[index];
}

void Player::removeBullet(unsigned index)
{
	if (index < 0 || index > this->bullets.size())
		throw ("OUT OF BOUNDS! PLAYER::GETBULLET!");

	return this->bullets.remove(index);
}

void Player::Update(Vector2u windowBounds,const float &dt)
{
    if (this->shootTimer < this->shootTimerMax)
		this->shootTimer += 1.f * dt * this->dtMultiplier;

	if (this->jumpTimer < this->jumpTimerMax)
		this->jumpTimer += 1.f * dt * this->dtMultiplier;

	if (this->damageTimer < this->damageTimerMax)
		this->damageTimer += 1.f *dt * this->dtMultiplier;

	this->Movement(dt);
	this->Combat(dt);
}
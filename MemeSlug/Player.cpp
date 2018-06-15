#include "Player.h"

unsigned Player::players = 0;

//Tipi di arma (temporaneo)
enum weapons{BULLET1 = 0, MISSILE, LASER};



Player::Player(std::vector<Texture> &textures, int ks, int ku, int pnts)
	: hpMax(50), damage(1), score(0)
{
	
	this->dtMultiplier = 60.f;

	this->faceRight = true;

	//Inizializzazione texture del player.

    this->sprite.setTexture(textures[0]);
	this->sprite.setScale(0.119f, 0.119f);
	this->sprite.setPosition(300.0f, 200.0f);
	this->playerBounds = this->sprite.getLocalBounds();
	this->hp = this->hpMax;
	
	this->piercingShot = false;

	//Inizializzazione delle textures dei bullets.
	this->bulletTexture = &textures[1];
	this->missileTexture = &textures[2];
	this->laserTexture = &textures[3];

	//Gestione frequenza Sparo
	this->shootTimerMax = 20;
	this->shootTimer = this->shootTimerMax;
	this->damageTimerMax = 40;
	this->damageTimer = this->damageTimerMax;

	//Inizializzazione achievements
	this->killSoldier = ks;
	this->killUfo = ku;
	this->points = pnts;

	//Frequenza salto.
	this->jumpTimerMax = 83;
	this->jumpTimer = this->jumpTimerMax;

	//Velocità, accelerazione e attrito. 
	this->maxVelocity = 8.0f;
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

int Player::getDamage() const 
{
	int damage = 0;

	switch (this->currentWeapon)
	{
	case BULLET1:

		damage = 3;
		
		break;
	
	case MISSILE:

		damage = 3;
		
		break;

	case LASER:

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
void Player::Movement(Vector2u windowBounds,const float &dt)
{
	//Update di normDir
	this->normDir = normalize(this->currentVelocity, vectorLength(this->currentVelocity));
	
	std::cout << "\n" << sprite.getPosition().x;

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
	 this->direction.y = -28.0f;


    	if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
		{
			this->currentVelocity.y = this->direction.y * this->acceleration * dt * this->dtMultiplier;

		}
		
		this->jumpTimer = 0;
	
	}

	if (this->sprite.getPosition().y < 680)
	{
		this->setGravity();
	
	}
	//Sinistra
	if (this->sprite.getPosition().x < this->LeftScreenBounds) 
	{
		this->sprite.setPosition(this->LeftScreenBounds, this->sprite.getPosition().y);
		this->currentVelocity.x = 0.f;
	}
	if (this->sprite.getPosition().x > this->RightScreenBounds)
	{
		this->sprite.setPosition(this->RightScreenBounds, this->sprite.getPosition().y);
		this->currentVelocity.x = 0.f;
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

//Metodo riguardante l'attacco del fucile del player 
void Player::Combat(const float &dt)
{
	if (Keyboard::isKeyPressed(Keyboard::A) && this->shootTimer >= this->shootTimerMax)
	{
		
		if (faceRight == true)
		{
			if (this->currentWeapon == BULLET1)
			{
				//crea i proiettili
				this->bullets.add(Bullet(bulletTexture, Vector2f(this->playerCenter.x + 40, this->playerCenter.y ),
					Vector2f(0.05f, 0.05f),
					 Vector2f(1.0f, 0.0f), 1.0f, 30.0f, 2.0f));
			}
			else if (this->currentWeapon == MISSILE)
			{
				//crea i missili
				this->bullets.add(Bullet(missileTexture, Vector2f(this->playerCenter.x + 40 , this->playerCenter.y),
					Vector2f(0.4f, 0.4f),
					 Vector2f(2.0f, 0.0f), 0.08f, 30.0f, 2.0f));
			}
			else if (this->currentWeapon == LASER)

				//crea il laser
				this->bullets.add(Bullet(laserTexture, Vector2f(this->playerCenter.x + 40, this->playerCenter.y ),
					Vector2f(1.f, 0.4f),
					Vector2f(20.0f, 0.0f), 0.8f, 40.0f, 2.0f));
		}
		else 
		{
			if (this->currentWeapon == BULLET1)
			{
				//crea i proiettili
				this->bullets.add(Bullet(bulletTexture, Vector2f(this->playerCenter.x - 140,this->playerCenter.y + 10),
					Vector2f(-0.05f, 0.05f),
					 Vector2f(-1.0f, 0.0f), 1.0f, 30.0f, 2.0f));
				
			}
			else if (this->currentWeapon == MISSILE)
			{
				//crea i missili
				this->bullets.add(Bullet(missileTexture, Vector2f(this->playerCenter.x - 200, this->playerCenter.y + 20),
					Vector2f(-0.4f, 0.4f),
					 Vector2f(-2.0f, 0.0f), 0.08f, 30.0f, 2.0f));
			}
			else if (this->currentWeapon == LASER)

				//crea il laser
				this->bullets.add(Bullet(laserTexture, Vector2f(this->playerCenter.x - 140, this->playerCenter.y),
					Vector2f(1.f, 0.4f),
					Vector2f(-20.0f, 0.0f), 0.04f, 30.0f, 2.0f));
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

void Player::CheckMapCollision(const float &dt, Vector2f platformPosition, FloatRect platformBounds)
{
	
	if (this->sprite.getGlobalBounds().intersects(platformBounds))
	{
		this->sprite.setPosition(this->sprite.getPosition().x, platformPosition.y - 140);
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

void Player::Reset()
{
	this->hpMax = 5;
	this->hp = this->hpMax;
	this->sprite.setPosition(Vector2f(300.f, 600.f));
	this->bullets.clear();
	this->piercingShot = false;
	this->currentVelocity.x = 0;
	this->currentVelocity.y = 0;
	this->currentWeapon = BULLET1;
	this->shootTimer = this->shootTimerMax;
	this->damageTimer = this->damageTimerMax;
	this->score = 0;
}

void Player::Update(Vector2u windowBounds,const float &dt)
{

	
    if (this->shootTimer < this->shootTimerMax)
		this->shootTimer += 1.f * dt * this->dtMultiplier;

	if (this->jumpTimer < this->jumpTimerMax)
		this->jumpTimer += 1.f * dt * this->dtMultiplier;

	if (this->damageTimer < this->damageTimerMax)
		this->damageTimer += 1.f *dt * this->dtMultiplier;

	this->Movement(windowBounds,dt);
	this->Combat(dt);
}

void Player::Notify() const
{
	
	for (auto itr = observer.begin(); itr != observer.end(); ++itr)
	{
		(*itr)->Modify(killSoldier, killUfo, points);

	}
}
	
	
void Player::Attach(Observer *o) 
{
		this->observer.push_back(o);
}

void Player::Detach(Observer *o)
{
	
		this->observer.remove(o);
	
}
			
		
void Player::SetKillSoldier() 
{
		this->killSoldier += 1;
		Changed();
		
}

void Player::SetKillUfo() 
{
		this->killUfo +=1;
		Changed();
		
}
	
void Player::SetPoints(int pnts) 
{
		this->points = pnts;
		Changed();
}



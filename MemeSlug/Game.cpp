#include "Game.h"

enum textures { player = 0, bullet1, missile };

Game::Game(RenderWindow *window)
{
	//Inizializzazione del gioco
	this->window = window;
	this->window->setFramerateLimit(60);
	this->dtMultiplier = 60.0f;
	this->runGame = true;
	this->scoreMultiplier = 1;
	this->score = 0;
	this->multiplierAdderMax = 10;
	this->multiplierAdder = 0;
	this->multiplierTimerMax = 400.f;
	this->multiplierTimer = this->multiplierTimerMax;
	

	this->InitTextures();
	
	
	//Inizializzazione dei fonts (UI ancora da implementare)
	this->font.loadFromFile("Fonts/Flighter_PERSONAL_USE_ONLY.ttf"); 


	//Creazione del player
	this->players.add(Player(this->textures));

	this->enemySpawnTimerMax = 80;
	this->enemySpawnTimer = this->enemySpawnTimerMax;



	this->InitUI();
	
}


Game::~Game()
{

}

void Game::InitTextures()
{
	//Inizializzazione delle textures
	this->textures.push_back(Texture());
	this->textures[player].loadFromFile("Textures/TarmaPlayer.png");
	this->textures.push_back(Texture());
	this->textures[bullet1].loadFromFile("Textures/bullet1.png");
	this->textures.push_back(Texture());
	this->textures[missile].loadFromFile("Textures/missile.png");


	Texture temp;
	temp.loadFromFile("Textures/SimpleSoldier.png");
	this->enemyTextures.add(Texture(temp));
	temp.loadFromFile("Textures/Ufo.png");
	this->enemyTextures.add(Texture(temp));
	temp.loadFromFile("Textures/soldierMSL.png");
	this->enemyTextures.add(Texture(temp));

	temp.loadFromFile("Textures/eBullet.png");
	this->enemyBulletTextures.add(Texture(temp));
}
//Ancora da completare
void Game:: InitUI()
{

	for (size_t i = 0; i < this->players.size(); i++)
	{
		
		this->staticPlayerText.setFont(font);
		this->staticPlayerText.setCharacterSize(12);
		this->staticPlayerText.setFillColor(Color::White);
		this->staticPlayerText.setString("");

		
	}

	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(Color(153,0,0,255));
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setString("YOU DIED");
	this->gameOverText.setPosition(this->window->getSize().x / 2 - 290, this->window->getSize().y / 2 - 100);


	this->scoreText.setFont(this->font);
	this->scoreText.setFillColor(Color(200, 200, 200, 150));
	this->scoreText.setCharacterSize(25);
	this->scoreText.setString("Score : 0");
	this->scoreText.setPosition(20.f, 20.f);
	

}

void Game:: UpdateUI()
{
	//STATIC TEXT 
}

void Game::DrawUI() 
{
	//STATIC TEXT

    if (this->runGame == false)
	{
		this->window->draw(this->gameOverText);
	}

	//Score 
	this->window->draw(this->scoreText);
}




//Update del game, si occupa di aggiornare le posizioni di players e bullets.
void Game::Update(const float &dt)
{
	if (this->players.size() > 0)
	{

		int h = 0;
		//Update timers
		if (this->enemySpawnTimer < this->enemySpawnTimerMax)
			this->enemySpawnTimer += 1.f* dt * this->dtMultiplier;

		//Score timer e moltiplicatori di score.
		if (this->multiplierTimer > 0.f)
		{
			this->multiplierTimer -= 1.f* dt * this->dtMultiplier;
			
			if (this->multiplierTimer <= 0.f)
			{
				this->multiplierTimer = 0.f;
				this->multiplierAdder = 0;
				this->scoreMultiplier = 1;
			}

		}
		

		this->scoreMultiplier = this->multiplierAdder / this->multiplierAdderMax + 1;


		//Enemies spawn
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemies.add(Enemy(this->enemyTextures, this->enemyBulletTextures,
				this->window->getSize(), Vector2f(rand() % this->window->getSize().x, 800.f),
				Vector2f(-1.f, 0.f), Vector2f(1.3f, 1.3f),
				0, 5, 3, 1,  0));

		    this->enemies.add(Enemy(this->enemyTextures, this->enemyBulletTextures,
				this->window->getSize(), Vector2f(rand() % this->window->getSize().x + 800, rand() % this->window->getSize().y - 500),
				Vector2f(-1.f, 0.f), Vector2f(0.15f, 0.15f),
				1, 5, 3, 1, 0));

		    this->enemies.add(Enemy(this->enemyTextures, this->enemyBulletTextures,
				this->window->getSize(), Vector2f(rand() % this->window->getSize().x, 730.f),
				Vector2f(-1.f, 0.f), Vector2f(0.28f, 0.28f),
				2, 5, 3, 1, 0));


			this->enemySpawnTimer = 0;
		}

		for (size_t i = 0; i < players.size(); i++)
		{
			if (this->players[i].isAlive())
			{
				//Update player.
				this->players[i].Player::Update(this->window->getSize(), dt);


				//Update Bullets
				for (size_t k = 0; k < this->players[i].getBulletsSize(); k++)
				{
					this->players[i].getBullet(k).Bullet::Update(dt);

					//Collisione tra bullet e enemies. 
					for (size_t j = 0; j < this->enemies.size(); j++)
					{
						if (this->players[i].getBullet(k).getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
						{
							this->players[i].removeBullet(k);

							if (this->enemies[j].getHP() > 0)
								this->enemies[j].takeDamage(this->players[i].getDamage());
							if (this->enemies[j].getHP() <= 0)
							{
								//Aggiunta score & Reset del multiplier timer
								this->multiplierTimer = this->multiplierTimerMax;
								int score = this->enemies[j].getHPMax() * this->scoreMultiplier;
								this->multiplierAdder++;	
								this->players[i].gainScore(score);


								this->enemies.remove(j);
							}
							return;

						}
					}

					//Per cancellare i bullet dopo la size della window.
					if (this->players[i].getBullet(k).getPosition().x > this->window->getSize().x)
					{
						this->players[i].removeBullet(k);
						return;
					}
				}
			}
			else
			{
				this->runGame = false;
			}

			//Update score
			this->score = 0;
			this->score += players[i].getScore();
			this->scoreText.setString("Score : " + std::to_string(score) +
				"\nMultiplier : " + std::to_string(this->scoreMultiplier) +
			    "\nMultiplier Timer : " + std::to_string((int)this->multiplierTimer) +
			    "\nNew Multiplier : " + std::to_string(this->multiplierAdder) + " / " +
			     std::to_string(this->multiplierAdderMax));


		}

		if (this->runGame == true)
		{
			//Update enemies.
			for (size_t i = 0; i < this->enemies.size(); i++)
			{
				this->enemies[i].Update(dt, this->players[this->enemies[i].getPlayerFollowNr()].getPosition());

				//Update dei proiettili del nemico.
				for (size_t k = 0; k < this->enemies[i].getBullets().size(); k++)
				{
					this->enemies[i].getBullets()[k].Update(dt);
				}
				//Gestione collisione tra player e enemies.
				for (size_t k = 0; k < this->players.size(); k++)
				{
				
					if (this->players[k].isAlive())
					{

						if (this->players[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds())
							&& !this->players[k].isDamagedCooldown())
						{
							this->players[k].takeDamage(this->enemies[i].getDamage());

						


							//this->enemies.remove(i);
							return;
						}
					}
				}


				if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
				{
					this->enemies.remove(i);
					return;
				}
			}
		}
		else
			this->enemySpawnTimer = 0;

		this->UpdateUI();
	}
}

//Disegnare a schermo players, boxes e bullets. 
void Game::Draw()
{
	this->window->clear();
	
	for (size_t i = 0; i < this->players.size(); i++)
	{
		this->players[i].Player::Draw(*this->window);
	}
	/*da sistemare
	for (size_t j = 0; j < this->boxes.size(); j++)
	{
		this->boxes[j].Box::Draw(*this->window);
	}
	*/

	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].Draw(*this->window);
	}
	this->DrawUI();

	this->window->display();

}


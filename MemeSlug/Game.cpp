#include "Game.h"

enum textures { player = 0, bullet1, missile };

Game::Game(RenderWindow *window)
{
	//Inizializzazione del gioco
	this->window = window;
	this->window->setFramerateLimit(60);
	this->dtMultiplier = 60.0f;
	this->runGame = true;

	this->InitTextures();
	
	
	//Inizializzazione dei fonts (UI ancora da implementare)
	this->font.loadFromFile("Fonts/Flighter_PERSONAL_USE_ONLY.ttf"); 


	//Creazione del player
	this->players.add(Player(this->textures));

	this->enemySpawnTimerMax = 80;
	this->enemySpawnTimer = this->enemySpawnTimerMax;



	//Creazione delle box (da implementare)
	
	//////////

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
	temp.loadFromFile("Textures/soldierMSL.png");
	this->enemyTextures.add(Texture(temp));
	temp.loadFromFile("Textures/Ufo.png");
	this->enemyTextures.add(Texture(temp));
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
}




//Update del game, si occupa di aggiornare le posizioni di players e bullets.
void Game::Update(const float &dt)
{
	if (this->players.size() > 0)
	{
		/*da sistemare
		for (size_t l = 0; l < this->boxes.size(); l++)
		{
			boxes[l].Box::Update();
		}
		*/

		int h = 0;
		//Update timers
		if (this->enemySpawnTimer < this->enemySpawnTimerMax)
			this->enemySpawnTimer += 1.f* dt * this->dtMultiplier;

		//Enemies spawn
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemies.add(Enemy(this->enemyTextures,
				this->window->getSize(), Vector2f(rand() % this->window->getSize().x, 700.f), 
				Vector2f(-1.f, 0.f), Vector2f(0.3f, 0.3f),
				0, 5, 3, 1 , 0));

			this->enemies.add(Enemy(this->enemyTextures,
				this->window->getSize(), Vector2f(rand() % this->window->getSize().x + 800, rand() % this->window->getSize().y - 500),
				Vector2f(-1.f, 0.f), Vector2f(0.15f, 0.15f),
				1, 5, 3, 1, 0));


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
								//Aggiunta score
								int score = this->enemies[j].getHPMax();
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
				this->runGame = false;
		}

		if (this->runGame == true)
		{
			//Update enemies.
			for (size_t i = 0; i < this->enemies.size(); i++)
			{
				this->enemies[i].Update(dt, this->players[this->enemies[i].getPlayerFollowNr()].getPosition());

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


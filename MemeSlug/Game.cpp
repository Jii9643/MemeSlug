#include "Game.h"

enum textures { player = 0, bullet1, missile, enemy01};

Game::Game(RenderWindow *window)
{
	//Inizializzazione del gioco
	this->window = window;
	this->window->setFramerateLimit(60);
	this->runGame = true;

	//Inizializzazione delle textures
	this->textures.push_back(Texture());
	this->textures[player].loadFromFile("Textures/TarmaPlayer.png");
	this->textures.push_back(Texture());
	this->textures[bullet1].loadFromFile("Textures/bullet1.png");
	this->textures.push_back(Texture());
	this->textures[missile].loadFromFile("Textures/missile.png");
	this->textures.push_back(Texture());
	this->textures[enemy01].loadFromFile("Textures/soldierMSL.png");
	
	//Inizializzazione dei fonts (UI ancora da implementare)
	this->font.loadFromFile("Fonts/Flighter_PERSONAL_USE_ONLY.ttf"); 


	//Creazione del player
	this->players.push_back(Player(this->textures));
	this->playersAlive = this->players.size();

	

	//Creazione degli enemies
	Enemy e1(&this->textures[enemy01],
		this->window->getSize(), Vector2f(1600.f, 700.f), 
		Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f), 
		0, 2, 1, 1);

	this->enemiesSaved.push_back(Enemy(e1));

	this->enemySpawnTimerMax = 80;
	this->enemySpawnTimer = this->enemySpawnTimerMax;



	//Creazione delle box (da implementare)
	
	//////////

	this->InitUI();
	
}


Game::~Game()
{

}

//Ancora da completare
void Game:: InitUI()
{
	Text tempText;

	for (size_t i = 0; i < this->players.size(); i++)
	{
		
		tempText.setFont(font);
		tempText.setCharacterSize(12);
		tempText.setFillColor(Color::White);
		tempText.setString("");

		this->staticPlayerTexts.push_back(Text(tempText));
	}

	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setString("YOU DIED");
	this->gameOverText.setPosition(this->window->getSize().x / 2 - 250, this->window->getSize().y / 2 - 100);

	

}

void Game:: UpdateUI()
{
	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++)
	{
		
	}
}

void Game::DrawUI() 
{
	for (size_t i = 0; i < this->staticPlayerTexts.size(); i++)
	{
		this->window->draw(this->staticPlayerTexts[i]);
	}

	if (this->runGame == false)
	{
		this->window->draw(this->gameOverText);
	}
}




//Update del game, si occupa di aggiornare le posizioni di players e bullets.
void Game::Update()
{
	if (this->players.size() > 0)
	{
		/*da sistemare
		for (size_t l = 0; l < this->boxes.size(); l++)
		{
			boxes[l].Box::Update();
		}
		*/

		//Update timers
		if (this->enemySpawnTimer < this->enemySpawnTimerMax)
			this->enemySpawnTimer++;

		//Enemies spawn
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemies.push_back(Enemy(&this->textures[enemy01],
				this->window->getSize(), Vector2f(rand() % this->window->getSize().x, 700.f),
				Vector2f(-1.f, 0.f), Vector2f(0.1f, 0.1f),
				0, rand() % 3 + 1, 3, 1));

			this->enemySpawnTimer = 0;
		}

		for (size_t i = 0; i < players.size(); i++)
		{
			if (this->players[i].isAlive())
			{
				//Update player.
				this->players[i].Player::Update();


				//Update Bullets
				for (size_t k = 0; k < this->players[i].getBullets().size(); k++)
				{
					this->players[i].getBullets()[k].Bullet::Update();

					//Collisione tra bullet e enemies. 
					for (size_t j = 0; j < this->enemies.size(); j++)
					{
						if (this->players[i].getBullets()[k].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()))
						{
							this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);

							if (this->enemies[j].getHP() > 0)
								this->enemies[j].takeDamage(this->players[i].getDamage());
							if (this->enemies[j].getHP() <= 0)

								this->enemies.erase(this->enemies.begin() + j);
							return;

						}
					}

					//Per cancellare i bullet dopo la size della window.
					if (this->players[i].getBullets()[k].getPosition().x > this->window->getSize().x)
					{
						this->players[i].getBullets().erase(this->players[i].getBullets().begin() + k);
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
				this->enemies[i].Update();

				//Gestione collisione tra player e enemies.
				for (size_t k = 0; k < this->players.size(); k++)
				{
					if (this->players[k].isAlive())
					{

						if (this->players[k].getGlobalBounds().intersects(this->enemies[i].getGlobalBounds()))
						{
							this->players[k].takeDamage(this->enemies[i].getDamage());


							this->enemies.erase(this->enemies.begin() + i);
							return;
						}
					}
				}


				if (this->enemies[i].getPosition().x < 0 - this->enemies[i].getGlobalBounds().width)
				{
					this->enemies.erase(this->enemies.begin() + i);
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


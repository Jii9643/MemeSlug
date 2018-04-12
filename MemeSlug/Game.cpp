#include "Game.h"

enum textures { player = 0, bullet1, missile};

Game::Game(RenderWindow *window)
{
	//Inizializzazione del gioco
	this->window = window;
	this->window->setFramerateLimit(60);
	
	//Inizializzazione delle textures
	this->textures.push_back(Texture());
	this->textures[player].loadFromFile("Textures/soldierMSR.png");
	this->textures.push_back(Texture());
	this->textures[bullet1].loadFromFile("Textures/bullet1.png");
	this->textures.push_back(Texture());
	this->textures[missile].loadFromFile("Textures/missile.png");
	this->textures.push_back(Texture());

	//Inizializzazione dei fonts (UI ancora da implementare)
	this->font.loadFromFile("Fonts/"); 

	//Creazione del player
	this->players.push_back(Player(this->textures));

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
}



//Update del game, si occupa di aggiornare le posizioni di players e bullets.
void Game::Update()
{
	/*da sistemare
	for (size_t l = 0; l < this->boxes.size(); l++)
	{
		boxes[l].Box::Update();
    }
	*/
	for (size_t i = 0; i < players.size(); i++)
	{
		this->players[i].Player::Update();
		for (size_t k = 0; k < this->players[i].getBullets().size(); k++)
		{
			this->players[i].getBullets()[k].Bullet::Update();
		}
	}
	this->UpdateUI();
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
	this->DrawUI();

	this->window->display();

}


#include "Game.h"



Game::Game(RenderWindow *window)
{
	this->window = window;
	this->window->setFramerateLimit(60);
	//Inizializzazione delle textures
	this->playerTexture.loadFromFile("Textures/Soldier.png");
	this->bulletTexture.loadFromFile("Textures/bullet1.png");
	this->boxTexture.loadFromFile("Textures/Box.png");

	//Inizializzazione del player
	this->players.push_back(Player(&playerTexture, &bulletTexture));
	this->boxes.push_back(Box(&boxTexture));

	


}


Game::~Game()
{

}


void Game::Update()
{
	for (size_t l = 0; l < this->boxes.size(); l++)
	{
		boxes[l].Box::Update();
	}
	for (size_t i = 0; i < players.size(); i++)
	{
		this->players[i].Player::Update();
		for (size_t k = 0; k < this->players[i].getBullets().size(); k++)
		{
			this->players[i].getBullets()[k].Bullet::Update();
		}
	}

}
void Game::Draw()
{
	this->window->clear();
	
	for (size_t i = 0; i < this->players.size(); i++)
	{
		players[i].Player::Draw(*this->window);
	}
	for (size_t j = 0; j < this->boxes.size(); j++)
	{
		boxes[j].Box::Draw(*this->window);
	}



	this->window->display();

}


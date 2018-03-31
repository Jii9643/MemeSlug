#include "Game.h"



Game::Game(RenderWindow *window)
{
	this->window = window;
	this->window->setFramerateLimit(60);
	//Inizializzazione delle textures
	this->playerTexture.loadFromFile("Textures/Soldier.png");
	this->bulletTexture.loadFromFile("Textures/bullet1.png");


	//Inizializzazione del player
	this->players.push_back(Player(&playerTexture, &bulletTexture));
	

}


Game::~Game()
{
	
}

void Game::Update()
{
	for (size_t i = 0; i < players.size(); i++) 
	{
		players[i].Update();
	}

}
void Game::Draw()
{
	this->window->clear();
	for (size_t i = 0; i < this->players.size(); i++)
	{
		players[i].Draw(*this->window);
	}
	this->window->display();
}
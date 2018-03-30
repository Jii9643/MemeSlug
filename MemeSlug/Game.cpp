#include "Game.h"



Game::Game(RenderWindow *window)
{
	this->window = window;
	//Inizializzazione delle textures
	playerTexture.loadFromFile("Textures/Soldier.png");


	//Inizializzazione del player
	player = new Player(&this->playerTexture);

}


Game::~Game()
{
	delete player;
}

void Game::Update() 
{
	player->Update();
}
void Game::Draw()
{
	window->clear();
	player->Draw(*window);
	window->display();
}
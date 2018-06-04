#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include "dArr.h"
#include <list>
#include "Observer.h"
#include "Subject.h"
#include "DisplayElement.h"

using namespace sf;

class Tile
 {
 public:
	 Tile(IntRect textureRect, Vector2f pos, bool isCollider, bool isDamaging);

	 virtual ~Tile();
	 //Static textures
	 static Texture tileTextures;

	 inline const Vector2f getPos()const { return this->sprite.getPosition(); }
	 inline const FloatRect getBounds()const { return this->sprite.getGlobalBounds(); }
	 inline const bool getIsDamaging()const { return this->isDamaging; }
	 inline const bool getIsCollider()const { return this->isCollider; }
	 inline void setPos(float x, float y) { this->sprite.setPosition(Vector2f(x, y)); }
	 inline void setTexRect(int x, int y, int width, int height) { this->sprite.setTextureRect(IntRect(x, y, width, height)); }
	 inline void setIsCollider(bool isCollider) { this->isCollider = isCollider; }
	 inline void setIsDamaging(bool idDamaging) { this->isDamaging = isDamaging; }

	 void Update();
	 void Draw(RenderTarget &target);

private:

	
	//Funzionalità
	bool isCollider;
	bool isDamaging;
	int damage;
	
	//Posizione
	
	//Visualizzazione
	Sprite sprite;  

};
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

class Map
{
public:
	
	Map(dArr<Texture> &textures, Vector2f position, Vector2f scale, Vector2u windowBounds, int type);

	inline FloatRect getGlobalBounds() const { return this->block.getGlobalBounds(); }
	inline Vector2f getPosition() const { return this->block.getPosition(); }
	inline const int& getType() const { return this->type; }
	virtual ~Map();

	//Funzioni 
	void Draw(RenderTarget &target);

private:

	dArr<Texture> *textures;
	Sprite block;
	Vector2u windowBounds;
	int type;

	float dtMultiplier;
};


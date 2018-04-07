#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <vector>

using namespace sf;

class Box 
{
public:
	Box();
	Box(Texture* texture);
	~Box();
	void Draw(RenderTarget& target);
    void Update();

	FloatRect boxBounds;
    static unsigned boxes;
	

private: 
	
	RectangleShape box;
	Texture* texture;
	Sprite sprite;
	
};


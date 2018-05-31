#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class DisplayElement {
	public:
	virtual void Display() = 0;


	virtual  ~DisplayElement() {};
			
};

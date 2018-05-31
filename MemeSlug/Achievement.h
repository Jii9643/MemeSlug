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

class Achievements : public Observer, private DisplayElement
{
public:
	explicit Achievements(Subject *playerach);
	~Achievements()override;
	virtual void Modify(int ks, int ku, int ptns) override;
	void Display();
	/*void SetAchievements();
	void LoadAch();*/



protected:
	char string [30] [255];
	Subject *playerach;
	int killSoldier;
	int killUfo;
	int points;
	bool Ach1, Ach2, Ach3;
	Text text;
	void Addstring2(std::string m);

};


#include "Achievement.h"



Achievements::Achievements(Subject *playerach) : killSoldier(0), killUfo(0), points(0) 
{
	
	this->playerach = playerach;
	Ach1 = false; 
	Ach2 = false; 
	Ach3 = false;
	playerach->Attach(this);
	
}

Achievements::~Achievements()
{
	playerach->Detach(this);
}


void Achievements::Modify(int ks, int ku, int pnts)
{
	this->killSoldier = ks;
	this->killUfo = ku;
	this->points = pnts;
	
	Display();
}

void Achievements::Display()
{


	if (this->killSoldier == 3 && this->Ach1 == false)
	{
		std::cout << "Morirete tutti!" << std::endl;
		this->Ach1 = true;;
	}

	if (this->killUfo == 3 && this->Ach2 == false)
	{
		std::cout << "Giro sull'ottovolante" << std::endl;
		this->Ach2 = true;
	}

	if (this->points == 20 && Ach3 == false)
	{
		std::cout << "Vacci piano" << std::endl;
		this->Ach3 = true;
	}
}






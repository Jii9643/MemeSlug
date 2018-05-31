#pragma once



class Observer {
public:
	
	virtual void Modify(int killSoldier, int killUfo, int points) = 0;
	virtual~Observer() {};


};

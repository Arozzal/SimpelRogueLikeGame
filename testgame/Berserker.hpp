#pragma once
#include "Mob.hpp"




class Berserker : public Mob{
public:
	void update(float frametime) override;
	void setMinion(bool);
	~Berserker() override{
		addItemPickupContainer(Ids);
	}
private:
	int speed = 50;
	int spawnsperr = 0;
	float diffx;
	int randomspawn;
	float diffy;
	bool active = false;
	bool foundX = false;
	bool foundY = false;
	bool minion = false;
};
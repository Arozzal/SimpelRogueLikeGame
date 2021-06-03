#pragma once
#include "Mob.hpp"

class Ghost : public Mob {
public:
	void update(float frametime) override;
private:
	int speed = 50;
	float goX;
	float goY;
	float diffx;
	float diffy;

};
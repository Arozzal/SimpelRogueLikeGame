#pragma once
#include "Mob.hpp"


class Walker : public Mob{
public:
	void update(float frametime) override;
private:
	const int speed = 100.f;
	unsigned int runs = 0;
	Direction dir = right;
	bool colllock = false;
};
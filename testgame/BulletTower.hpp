#pragma once
#include "Mob.hpp"


class BulletTower : public Mob {
public:
	void update(float frametime) override;
private:
	float direction = 1;
	float Radian;
	sf::Vector2f bulletangle;
	void rerollstats();
	int octa = 0;
};
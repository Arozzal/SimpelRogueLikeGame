#include "BulletTower.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "ListManager.hpp"
extern Player player;

void BulletTower::update(float frametime){

	rerollstats();

	if (!octa) {

		switch (art) {
		case 0:
			LM::PushBulletlist()->emplace_back(200, getX(), getY(), bulletangle, direction + 90, false);
			direction += 16;
			break;
		case 1:

			float tempradian = Radian;
			sf::Vector2f tempangle = bulletangle;

			direction += 90;
			rerollstats();

			LM::PushBulletlist()->emplace_back(200, getX(), getY(), bulletangle, direction + 90, false);

			direction += 90;
			rerollstats();

			LM::PushBulletlist()->emplace_back(200, getX(), getY(), bulletangle, direction + 90, false);

			direction += 90;
			rerollstats();

			LM::PushBulletlist()->emplace_back(200, getX(), getY(), bulletangle, direction + 90, false);

			direction += 90;
			rerollstats();

			LM::PushBulletlist()->emplace_back(200, getX(), getY(), bulletangle, direction + 90, false);
			direction += 16;


			break;
		}
		
	}

	octa++;

	if (octa > 18) {
		octa = 0;
	}
}

void BulletTower::rerollstats(){
	Radian = (direction / 180 * 3.141);
	bulletangle = sf::Vector2f(std::cos(Radian), std::sin(Radian));
}

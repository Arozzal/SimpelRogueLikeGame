#include "Berserker.hpp"
#include "Player.hpp"
#include "Framework.hpp"
#include "Blood.hpp"
#include "Walker.hpp"
#include "ListManager.hpp"
#include <cstdlib>
#include <ctime>

extern Player player;

void Berserker::update(float frametime){
	if (active) {
		diffx = (player.getPlayerPosX() - getX());
		diffy = (player.getPlayerPosY() - getY());
		float goX = 0;
		float goY = 0;
		

		if (diffx > 20 || diffx < -20) {
			if (player.getPlayerPosX() > getX()) {
				goX = speed;
			}
			else if (player.getPlayerPosX() < getX()) {
				goX = -speed;
			}
			foundX = false;
		}
		else {
			foundX = true;
		}


		if (diffy > 20 || diffy < -20) {
			if (player.getPlayerPosY() > getY()) {
				goY = speed;
			}
			else if (player.getPlayerPosY() < getY()) {
				goY = -speed;
			}
			foundY = false;
		}
		else {
			foundY = true;
		}

		if (foundX || foundY) {
			goX *= 4;
			goY *= 4;

			srand(time(NULL));

			int random = rand() % 2;
			
			randomspawn = rand() % 7;
			
			if (random == 1) {
				Block *blood = new Blood;
				blood->create(64.f, 64.f);
				blood->setColor(Color::RED);
				blood->setPosition(getX(), getY());
				//Framework::getFwData()->notCollidingBlocks->push_back(blood);
				LM::PushNotColliding(blood);
			}

			if (randomspawn == 1 && spawnsperr <= 0) {
				spawnsperr = 30;
				Mob *mob1 = new Walker;
				mob1->setHp(10);
				mob1->create(62, 62);
				mob1->setColor(Color::YELLOW);
				mob1->setPosition(getX(), getY());
				LM::PushMob(mob1);
			}

			if (spawnsperr > 0) {
				spawnsperr--;
			}

		}


		if (Collision::BoundingBoxTest(*player.getImage(), (*getImage()))) {
			player.doDmg(20);
		}

		setPosition((getX() + (goX * frametime)), (getY() + (goY * frametime)));
	}else {

		diffx = (player.getPlayerPosX() - getX());
		diffy = (player.getPlayerPosY() - getY());
		if ((diffx < 100 && diffx > -100) && (diffy < 100 && diffy > -100)) {
			player.setHp(121);
			active = true;
		}

		setHp(300);
	}
}

void Berserker::setMinion(bool minion){
	this->minion = minion;
}

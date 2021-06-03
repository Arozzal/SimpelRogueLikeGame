#include "Walker.hpp"
#include "Player.hpp"
#include "CollisionSystem.hpp"
extern Player player;

void Walker::update(float frametime){
	float diffx = (player.getPlayerPosX() - getX());
	float diffy = (player.getPlayerPosY() - getY());
	float goX = 0;
	float goY = 0;
	if (!runs) {
		colllock = false;
	}

	if (!colllock) {
		if (diffx > 10 || diffx < -10) {
			if (player.getPlayerPosX() > getX()) {
				goX = speed;
			}
			else if (player.getPlayerPosX() < getX()) {
				goX = -speed;
			}
		}
		if (diffy > 10 || diffy < -10) {
			if (player.getPlayerPosY() > getY()) {
				goY = speed;
			}
			else if (player.getPlayerPosY() < getY()) {
				goY = -speed;
			}
		}
	}
	else if (colllock) {
		switch (dir) {
		case right:
			goX = speed;
			break;
		case down:
			goY = speed;
			break;
		case left:
			goX = -speed;
			break;
		case up:
			goY = -speed;
			break;
		}
		runs--;
	}
	float posnowx = getX();
	float posnowy = getY();

	setPosition((posnowx + (goX * frametime)), (posnowy + (goY * frametime)));

	if (Collision::BoundingBoxTest(*player.getImage(), (*getImage()))) {
		player.doDmg(5);
	}

	if (CollSystem::collideSolidForBullets(getImage(), true)) {
		setPosition(posnowx, posnowy);
		runs = 100;
		colllock = true;
		dir = getNextDir(dir);
	}
}

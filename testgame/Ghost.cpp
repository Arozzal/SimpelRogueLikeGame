#include "Ghost.hpp"
#include "Player.hpp"

extern Player player;

void Ghost::update(float frametime) {

	diffx = (player.getPlayerPosX() - getX());
	diffy = (player.getPlayerPosY() - getY());
	goX = 0;
	goY = 0;


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
	float posnowx = getX();
	float posnowy = getY();

	if (Collision::BoundingBoxTest(*player.getImage(), (*getImage()))) {
		player.doDmg(5);
	}

	setPosition((posnowx + (goX * frametime)), (posnowy + (goY * frametime)));
}

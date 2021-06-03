#include "Blood.hpp"
#include "Player.hpp"

extern Player player;

int Blood::third = 0;

void Blood::update(float){
	if (third >= 16) {
		third = 0;
	}
	if (third <= 5) {
		setColor(Color::MAGNETA);
	}else {
		setColor(Color::RED);
	}
	if (Collision::CircleTest(*player.getImage(), *getImage())) {
		player.doDmg(10);
	}

	
}

void Blood::thirdplus() {
	third++;
}
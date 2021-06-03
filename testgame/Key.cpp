#include "Key.hpp"
#include "Keyblock.hpp"
#include "CollisionSystem.hpp"
#include <SFML\Graphics.hpp>

extern Player player;

void Key::update(float){

	if (Collision::CircleTest(*player.getImage(), *getImage())) {
		Keyblock::setLocked(false);
		setPosition(10000.f, 10000.f);
	}

}

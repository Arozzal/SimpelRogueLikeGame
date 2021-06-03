#include "Keyblock.hpp"
#include "Block.hpp"
#include <iostream>

bool Keyblock::locked = true;

void Keyblock::update(float frametime){
	if (!locked) {
		setPosition(1000.f, 1000.f);
	}
}

bool Keyblock::getLocked(){
	return locked;
}

void Keyblock::setLocked(bool locked){
	Keyblock::locked = locked;
}

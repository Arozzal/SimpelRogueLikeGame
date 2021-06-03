#include "Mob.hpp"
#include "Player.hpp"
#include "Collision.hpp"
#include <SFML\Graphics.hpp>

extern Player player;

Mob::Mob() {
	hpfont.loadFromFile("font.otf");
	hptext.setString(std::to_string(hp));
	hptext.setFont(hpfont);
	hptext.setColor(sf::Color(250, 250, 250, 250));
	hp = 3;
	
}
Direction Mob::getNextDir(Direction direction){
	switch (direction) {
	case right:
		return down;
	case down:
		return left;
	case left:
		return up;
	case up:
		return right;
	}
	
	return down;
}


int Mob::getHp() {
	
	return this->hp;
}
void Mob::setHp(int hp) {
	this->hp = hp;
	hptext.setString(std::to_string(hp));
	hptext.setOrigin(sf::Vector2f(hptext.getLocalBounds().width / 2, hptext.getLocalBounds().height / 2));
}

void Mob::setMapgrid(std::vector<std::vector<int>> mapgrid){
	this->mapgrid = mapgrid;
	std::vector<int> row(mapgrid[0].size(), mapgrid[0].size());
	closedlist.resize(mapgrid.size(), row);
}


sf::Text* Mob::getHpBar() {
	hptext.setPosition(sprite.getPosition().x ,sprite.getPosition().y - 64);
	return &hptext;
}

void Mob::setart(int art){
	this->art = art;
}


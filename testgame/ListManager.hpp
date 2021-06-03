#pragma once
#include <vector>
#include <list>

#include "Bullet.hpp"
#include "Mob.hpp"
#include "Block.hpp"
namespace LM {

	void set(std::list<Bullet>* bulletlist, std::vector<Block*>* onlyDrawBlocks, std::vector<Block*>* updateDrawBlocks, std::vector<Mob*>* moblist
	   , std::vector<Block*>* onlyupdateblocks, std::vector<Block*>* notcollidingblocks, sf::RenderWindow*, sf::Vector2i* mapglobalcords, int* mapnumber, bool* running);

	std::list<Bullet>* PushBulletlist();

	void PushOnlyDraw(Block*);
	void PushUpdateDraw(Block*);
	void PushMob(Mob*);
	void PushOnlyUpdate(Block*);
	void PushNotColliding(Block*);

	int* getMapNumber();

	void setRunning(bool);

	sf::RenderWindow* getWindow();
	sf::Vector2i* getGlobalMapCords();
}
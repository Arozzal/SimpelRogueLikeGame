#pragma once
#include <vector>
#include "Block.hpp"
#include "Mob.hpp"
#include "MapTrigger.hpp"
#include <SFML\Graphics.hpp>
#include "Collision.hpp"
#include "Player.hpp"
#include <thread>
#include <iostream>

namespace CollSystem {

	struct Collisiondata {
		std::vector<Block*>* onlyDrawBlocks;
		std::vector<Mob*>* Moblist;
		std::vector<Block*>* onlyupdateBlocks;
		std::vector<Block*>* updateDrawBlocks;
		std::vector<std::vector<int>> *mapgrid;
		int posobjx;
		int posobjy;
	};

	bool collideSolid(sf::Sprite*);

	bool collideSolidForBullets(sf::Sprite* object1, bool enemy = false);

	bool collideEnemy(sf::Sprite*);

	bool collidePlayer(sf::Sprite*);

	void set(std::vector<Block*>* onlyDrawBlocks, std::vector<Block*>* updateDrawBlocks, std::vector<Mob*>* Moblist, std::vector<Block*>* onlyupdateBlocks);
	
	void setGrid(std::vector<std::vector<int>> *mapgrid);
}
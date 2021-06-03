#pragma once
#include <iostream>
#include <String>
#include <SFML\Graphics.hpp>
#include "Block.hpp"
#include <fstream>
#include <vector>
#include <list>
#include "Mob.hpp"
#include "Bullet.hpp"
#include "Ghost.hpp"
#include "MapTrigger.hpp"

namespace Maploader {

	//Player Spawn Point reset
	void reset();
	
	//Verknüpfung Listen
	void set(std::list<Bullet>* bulletlist,std::vector<Block*>* onlyDrawBlocks, std::vector<Block*>* updateDrawBlocks, std::vector<Mob*>*, std::vector<Block*>*, std::vector<Block*>*);

	void load(std::string);

	void create(Direction);
	
	void destroy();

	//Map Size Buffer[0]
	int getMapXSize();

	//Map Size Buffer[1]
	int getMapYSize();

	//Returnt die Speicher Liste Liste für aufgesammelte Items
	std::map<sf::String, bool>* getItemDataMap();

	//Returnt das Mapgrid mit den Int Werten aller Objecte auf der Map.
	std::vector<std::vector<int>> *getMapgrid();
}
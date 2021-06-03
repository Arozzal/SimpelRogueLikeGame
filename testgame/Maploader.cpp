#include <iostream>
#include <fstream>
#include <Windows.h>
#include <list>
#include <map>

#include "Maploader.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include "MapTrigger.hpp"
#include "Ghost.hpp"
#include "Berserker.hpp"
#include "Walker.hpp"
#include "ConfigFile.hpp"
#include "Finder.hpp"
#include "Keyblock.hpp"
#include "Key.hpp"
#include "Blood.hpp"
#include "BulletTower.hpp"
#include "Items.hpp"
#include "ListManager.hpp"
#include "CollisionSystem.hpp"

extern Player player;

namespace Maploader {
	
	struct Mapdata {


		std::vector<std::vector<int>> mapgrid;
		
		
		std::map<sf::String, bool> ItemPickupt;

		char* buffer;
		bool startpositionlock = false;

		std::list<Bullet>* bulletlist;
		std::vector<Block*>* updateDrawBlocks;
		std::vector<Block*>* onlyDrawBlocks;

		int Mapxsize = 0;
		int Mapysize = 0;

		std::vector<Mob*>* Moblist;
		std::vector<Block*>* onlyupdateBlocks;
		std::vector<Block*>* notCollidingBlocks;
	};

	Mapdata data;

	std::map<sf::String, bool>* Maploader::getItemDataMap() {
		return &data.ItemPickupt;
	}

	void Maploader::reset(){
		data.startpositionlock = false;
	}

	void set(std::list<Bullet>* bulletlist, std::vector<Block*>* onlyDrawBlocks, std::vector<Block*>* updateDrawBlocks, std::vector<Mob*>* Moblist, std::vector<Block*>* onlyupdateBlocks, std::vector<Block*> *notCollidingBlocks) {
		data.bulletlist = bulletlist;
		data.onlyDrawBlocks = onlyDrawBlocks;
		data.updateDrawBlocks = updateDrawBlocks;
		data.Moblist = Moblist;
		data.onlyupdateBlocks = onlyupdateBlocks;
		data.notCollidingBlocks = notCollidingBlocks;
	}



	void load(std::string path) {


		const int FILESIZE = 10000;


		data.buffer = new char[FILESIZE];
		std::ifstream file;
		file.open(path, std::ios::ate | std::ios::binary);
		file.seekg(0, std::ios::beg);




		if (file.is_open()) {


			file.read(data.buffer, FILESIZE);

			std::cout << static_cast<int>(data.buffer[0]) << std::endl;
			std::cout << static_cast<int>(data.buffer[1]) << std::endl;

			std::vector<int> row(data.buffer[1], data.buffer[1]);


			data.mapgrid.resize(data.buffer[0], row);

			data.Mapxsize = data.buffer[0];
			data.Mapysize = data.buffer[1];

			file.close();
		}
		else {
			std::cerr << "Not exist " + path << std::endl;
		}



		int count = 0;
		for (int i = 0; i < data.mapgrid.size(); i++) {
			for (int d = 0; d < data.mapgrid[i].size(); d++) {

				data.mapgrid[i][d] = data.buffer[count+2];
				count++;
			}
		}

		CollSystem::setGrid(&data.mapgrid);
	}




	void Maploader::create(Direction dir) {

		for (int i = 0; i < data.mapgrid.size(); i++) {
			for (int d = 0; d < data.mapgrid[i].size(); d++) {

				Color col = Color::BLACK;
				if (data.ItemPickupt.find(std::to_string(i) + "." + std::to_string(d)
					+ "." + std::to_string(LM::getGlobalMapCords()->x) + "." + std::to_string(LM::getGlobalMapCords()->y)) == data.ItemPickupt.end()) {

					/*if (atoi(ConfigFile::getValue("Disable").c_str()) == data.mapgrid[i][d]) {
						continue;
					}*/


					switch (data.mapgrid[i][d]) {
					case 2:case 3:case 4:case 5:case 6: case 7: case 8:case 9: {
						Block *block = new Block;

						block->create("images/Block" + std::to_string(data.mapgrid[i][d]) + ".png");


						block->setPosition(64.f*i, 64.f*d);

						data.onlyDrawBlocks->push_back(block);
						break;
					}case 21: {
						Block *keyblock = new Keyblock;
						keyblock->setPosition(64.f*i, 64.f*d);
						keyblock->create("images/Keyblock.png");
						data.updateDrawBlocks->push_back(keyblock);
						break;
					}case 22: {
						Block *key = new Key;
						key->setPosition(64.f*i, 64.f*d);
						key->setSize(2.f, 2.f);
						key->create("images/Key.png");
						data.notCollidingBlocks->push_back(key);
						break;
					}case 30: {
						Block *blood = new Blood;
						blood->setPosition(64.f*i, 64.f*d);
						blood->setSize(2.f, 2.f);
						blood->setColor(Color::RED);
						blood->create(64.f, 64.f);
						data.notCollidingBlocks->push_back(blood);
						break;
					}case 45: case 46: {
						Mob *tower = new BulletTower;
						tower->setPosition(64.f*i, 64.f*d);
						if (data.mapgrid[i][d] == 45) {
							tower->setart(0);
							tower->setColor(Color::MAGNETA);
							tower->setHp(50);
						}
						else {
							tower->setart(1);
							tower->setColor(Color::PURPLE);
							tower->setHp(150);
						}
						tower->create(64.f, 64.f);
						data.Moblist->push_back(tower);
						break;
					}case 48: {
						Mob *mob1 = new Walker;
						mob1->setHp(10);
						mob1->create(62, 62);
						mob1->setColor(Color::RED);
						mob1->setPosition(64.f*i, 64.f*d);
						data.Moblist->push_back(mob1);
						break;
					}case 49: {
						Mob *ghost = new Ghost;
						ghost->setHp(25);
						ghost->create(62, 62);
						ghost->setColor(Color::GREEN);
						ghost->setPosition(64.f*i, 64.f*d);
						data.Moblist->push_back(ghost);
						break;
					}case 50: {
						Mob *berserker = new Berserker;
						berserker->setHp(500);
						berserker->setIds(i, d);
						berserker->create(62 * 1.5, 62 * 1.5);
						berserker->setColor(Color::YELLOW);
						berserker->setPosition(64.f*i, 64.f*d);
						data.Moblist->push_back(berserker);
						break;
					}case 51: {
						/*	Mob *finder = new Finder;
							finder->setHp(30);
							finder->create(62, 62);
							finder->setColor(Color::CYAN);
							finder->setPosition(64.f*i, 64.f*d);
							finder->setMapgrid(data.mapgrid);
							data.Moblist->push_back(finder);*/
						break;
					}case 70: {
						Block *speed = new SpeedItem();
						speed->setIds(i, d);
						speed->setPosition(64.f*i, 64.f*d);
						speed->setSize(2.f, 2.f);
						speed->create("images/Speed_Item.png");
						data.notCollidingBlocks->push_back(speed);
						break;
					}case 71: {
						Block *bullitem = new BulletUpgradeItem();
						bullitem->setPosition(64.f*i, 64.f*d);
						bullitem->setSize(2.f, 2.f);
						bullitem->setIds(i, d);
						bullitem->create("images/Bullet_Upgrade_Item.png");
						data.notCollidingBlocks->push_back(bullitem);
						break;
					}case 72: {
						Block *bullitem = new BulletSpeedUpgradeItem();
						bullitem->setPosition(64.f*i, 64.f*d);
						bullitem->setSize(2.f, 2.f);
						bullitem->setIds(i, d);
						bullitem->create("images/Bullet_Upgrade_Speed_Item.png");
						data.notCollidingBlocks->push_back(bullitem);
						break;
					}case 73: {
						Block *bullitem = new BulletAtShotUpgradeItem();
						bullitem->setPosition(64.f*i, 64.f*d);
						bullitem->setSize(2.f, 2.f);
						bullitem->setIds(i, d);
						bullitem->create("images/Bullet_Upgrade_Add_Item.png");
						data.notCollidingBlocks->push_back(bullitem);
						break;
					}case 74: {
						Block *bullitem = new ShieldUpgradeItem();
						bullitem->setPosition(64.f*i, 64.f*d);
						bullitem->setSize(2.f, 2.f);
						bullitem->setIds(i, d);
						bullitem->create("images/Shield_Upgrade_Item.png");
						data.notCollidingBlocks->push_back(bullitem);
						break;
					}case 123: {
						if (!data.startpositionlock) {
							player.setPos(63.f*i, 63.f*d);
							data.startpositionlock = true;
						}
						break;
					}case 124: {
						if (dir == up) {
							player.setPos(63.f*i, 63.f*d);
						}
						break;
					}case 125: {
						if (dir == right) {
							player.setPos(63.f*i, 63.f*d);
						}
						break;
					}case 126: {
						if (dir == down) {
							player.setPos(63.f*i, 63.f*d);
						}
						break;
					}case 127: {
						if (dir == left) {
							player.setPos(63.f*i, 63.f*d);
						}
						break;
					}	case 32: case 33: case 34: case 35: {
						Block *Trigger = new MapTrigger;
						switch (data.mapgrid[i][d]) {
						case 32:
							Trigger->setDirection(Direction::up);
							break;
						case 33:
							Trigger->setDirection(Direction::right);
							break;
						case 34:
							Trigger->setDirection(Direction::down);
							break;
						case 35:
							Trigger->setDirection(Direction::left);
							break;

						}
						Trigger->create(64, 64);
						Trigger->setPosition(64.f*i, 64.f*d);
						data.onlyupdateBlocks->push_back(Trigger);
						break;
					}
					}
				}
				std::cout << data.mapgrid[i][d] << " ";
			}
			std::cout << std::endl;
		}
	}





	void Maploader::destroy() {
		for (auto it = data.Moblist->begin(); it != data.Moblist->end(); ++it) {
			delete (*it);
		}
		data.Moblist->clear();
		data.Moblist->resize(0);

		/*for (auto it = data.bulletlist->begin(); it != data.bulletlist->end(); ++it) {
			delete (*it);
		}*/
	//	data.bulletlist->clear();
	//	data.bulletlist->resize(0);

		data.mapgrid.clear();
		data.mapgrid.resize(0);

		for (auto it = data.notCollidingBlocks->begin(); it != data.notCollidingBlocks->end(); ++it) {
			delete (*it);
		}
		data.notCollidingBlocks->clear();
		data.notCollidingBlocks->resize(0);

		for (auto it = data.onlyDrawBlocks->begin(); it != data.onlyDrawBlocks->end(); ++it) {
			delete (*it);
		}
		data.onlyDrawBlocks->clear();
		data.onlyDrawBlocks->resize(0);

		for (auto it = data.updateDrawBlocks->begin(); it != data.updateDrawBlocks->end(); ++it) {
			delete (*it);
		}
		data.updateDrawBlocks->clear();
		data.updateDrawBlocks->resize(0);

		for (auto it = data.onlyupdateBlocks->begin(); it != data.onlyupdateBlocks->end(); ++it) {
			delete (*it);
		}
		data.onlyupdateBlocks->clear();
		data.onlyupdateBlocks->resize(0);
		delete[] data.buffer;

	}
}

std::vector<std::vector<int>>* Maploader::getMapgrid(){
	return &data.mapgrid;
}

int Maploader::getMapXSize() {
	return data.Mapxsize;
}

int Maploader::getMapYSize() {
	return data.Mapysize;
}
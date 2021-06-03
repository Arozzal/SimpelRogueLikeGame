#include "ListManager.hpp"
namespace LM {

	struct Lists {
		std::list<Bullet>* bulletlist;
		std::vector<Block*>* updateDrawBlocks;
		std::vector<Block*>* onlyDrawBlocks;
		std::vector<Mob*>* Moblist;
		std::vector<Block*>* onlyupdateBlocks;
		std::vector<Block*>* notCollidingBlocks;
		sf::RenderWindow *window;

		bool* running;

		sf::Vector2i* mapglobalcords;

		int* mapnumber;
	};

	Lists data;
	void set(std::list<Bullet>* bulletlist, std::vector<Block*>* onlyDrawBlocks, std::vector<Block*>* updateDrawBlocks, std::vector<Mob*>* Moblist,
		std::vector<Block*>* onlyupdateBlocks, std::vector<Block*>* notCollidingBlocks, sf::RenderWindow *window, sf::Vector2i* mapglobalcords, int* mapnumber, bool* running) {
		data.bulletlist = bulletlist;
		data.onlyDrawBlocks = onlyDrawBlocks;
		data.updateDrawBlocks = updateDrawBlocks;
		data.Moblist = Moblist;
		data.onlyupdateBlocks = onlyupdateBlocks;
		data.notCollidingBlocks = notCollidingBlocks;
		data.window = window;
		data.running = running;

		data.mapglobalcords = mapglobalcords;
		data.mapnumber = mapnumber;
	}

	std::list<Bullet>* PushBulletlist() {
		return data.bulletlist;
		//data.bulletlist->push_back(object);
	}
	void PushOnlyDraw(Block* object) {
		data.onlyDrawBlocks->push_back(object);
	}
	void PushUpdateDraw(Block* object) {
		data.updateDrawBlocks->push_back(object);
	}
	void PushMob(Mob* object) {
		data.Moblist->push_back(object);
	}
	void PushOnlyUpdate(Block* object ) {
		data.onlyupdateBlocks->push_back(object);
	}
	void PushNotColliding(Block* object ) {
		data.notCollidingBlocks->push_back(object);
	}

	sf::Vector2i* getGlobalMapCords() {
		return data.mapglobalcords;
	}


	int* getMapNumber() {
		return data.mapnumber;
	}

	void setRunning(bool running){
		*data.running = running;
	}

	sf::RenderWindow* getWindow() {
		return data.window;
	}
}
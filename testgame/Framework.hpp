#pragma once
#include <SFML\Graphics.hpp>
#include "Mob.hpp"
#include <vector>
#include <list>
#include "Maploader.hpp"
#include "Bullet.hpp"
#include "MapTrigger.hpp"
#include "Button.hpp"
#include "GuiManager.hpp"




class Framework {
private:
	sf::Vector2i mapglobalcords;
	int mapnumber = 1;
	
	sf::Font font;

	sf::Clock *pclock;
	float currentframtime;
	sf::RenderWindow *Window;
	sf::View *view;
	sf::View *guiview;
	sf::Event *Event;
	sf::Text *hptext;

	GuiManager* guimanager;


	bool running = true;
	std::list<Bullet> *bullet;
	std::vector<Mob*> *mob;
	std::vector<Block*> *onlyDrawBlocks;
	std::vector<Block*> *updateDrawBlocks;
	std::vector<Block*> *onlyupdateBlocks;
	std::vector<Block*> *notCollidingBlocks;
public:
	void setPlayerHp(int hp);
	void setrunning(bool);
	bool getrunning();
	void init(std::string startarg = "");
	float getFrameTime();
	void update();
	void eventhandle();
	void draw();

	~Framework() {
		delete Window;
		delete pclock;
		delete view;
		delete guiview;
		delete hptext;
		delete Event;
		delete guimanager;
		
		for (auto it = onlyDrawBlocks->begin(); it != onlyDrawBlocks->end(); ++it) {
			delete (*it);
		}

		for (auto it = updateDrawBlocks->begin(); it != updateDrawBlocks->end(); ++it) {
			delete (*it);
		}

		for (auto it = onlyupdateBlocks->begin(); it != onlyupdateBlocks->end(); ++it) {
			delete (*it);
		}

		for (auto it = notCollidingBlocks->begin(); it != notCollidingBlocks->end(); ++it) {
			delete (*it);
		}


		for (auto it = mob->begin(); it != mob->end(); ++it) {
			delete (*it);
		}
		
		delete onlyDrawBlocks;
		delete updateDrawBlocks;
		delete onlyupdateBlocks;
		delete notCollidingBlocks;
		delete mob;
		delete bullet;
	}
};

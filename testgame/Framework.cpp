#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include <list>
#include <string>

#include "Framework.hpp"
#include "Player.hpp"
#include "Event.hpp"
#include "Maploader.hpp"
#include "MapTrigger.hpp"
#include "ConfigFile.hpp"
#include "Mob.hpp"
#include "Bullet.hpp"
#include "CollisionSystem.hpp"
#include "Blood.hpp"
#include "ListManager.hpp"
#include "GuiObj.hpp"

bool active = false;

sf::Font hfont;

Player player(60.f, 60.f, 60.f, 60.f);


float Framework::getFrameTime() {
	currentframtime = pclock->getElapsedTime().asSeconds();
	pclock->restart();
	//std::cout << currentframtime << std::endl;
	return currentframtime;
}



//INIT METHOD
void Framework::init(std::string startarg) {
	mapglobalcords.x = 1;
	mapglobalcords.y = 2;

	pclock = new sf::Clock;
	Window = new sf::RenderWindow(sf::VideoMode(1600, 900, 32), "Game", sf::Style::None);
	Event = new sf::Event;
	view = new sf::View(sf::FloatRect(0, 0, 1600, 900));
	guiview = new sf::View(sf::FloatRect(0, 0, 1600, 900));
	hfont.loadFromFile("font.otf");
	
	
	mob = new std::vector<Mob*>;
	onlyDrawBlocks = new std::vector<Block*>;
	updateDrawBlocks = new std::vector<Block*>;
	onlyupdateBlocks = new std::vector<Block*>;
	notCollidingBlocks = new std::vector<Block*>;
	bullet = new std::list<Bullet>;

	hptext = new sf::Text("NULL", (hfont), 20);
	hptext->setOutlineColor(sf::Color(0, 0, 0, 255));
	hptext->setColor(sf::Color(250, 250, 250, 250));



	Maploader::set(bullet, onlyDrawBlocks, updateDrawBlocks, mob, onlyupdateBlocks, notCollidingBlocks);
	LM::set(bullet, onlyDrawBlocks, updateDrawBlocks, mob, onlyupdateBlocks, notCollidingBlocks, Window, &mapglobalcords, &mapnumber, &running);
	CollSystem::set(onlyDrawBlocks, updateDrawBlocks, mob, onlyupdateBlocks);

	Window->setFramerateLimit(30);

	
	ConfigFile::setMap();

	std::string mapstr = ConfigFile::getValue("Start");

	player.setHp(atoi(ConfigFile::getValue("Player.Hp").c_str()));

	std::cout << ConfigFile::getValue("Player.Hp");

	if (startarg != "") {
		Maploader::load(startarg);
	}else {
		Maploader::load("map" + std::to_string(mapnumber) + "/" + mapstr);
	}
	Maploader::create(down);


	guimanager = new GuiManager;
}


//UPDATE METHOD
void Framework::update() {
	if (guimanager->getGuiNumber() == 0) {
		float frametime = getFrameTime();

		if (player.getHp() < 0) {
			Maploader::reset();
			player.setHp(100);
			running = false;
		}

		player.update(frametime, (bullet));

		sf::String temphptext = std::to_string(player.getHp());
		hptext->setString(temphptext);

		Blood::thirdplus();

		for (int i = 0; i < onlyupdateBlocks->size(); i++) {
			(*onlyupdateBlocks)[i]->update(frametime);
		}

		
		for (std::vector<Block*>::iterator it = updateDrawBlocks->begin(); it != updateDrawBlocks->end(); ++it) {
			(*it)->update(frametime);
		}

		for (std::vector<Block*>::iterator it = notCollidingBlocks->begin(); it != notCollidingBlocks->end(); ++it) {
			(*it)->update(frametime);
		}

		for (std::vector<Mob*>::iterator it = mob->begin(); it != mob->end();) {
			(*it)->update(frametime);
			if ((*it)->getHp() <= 0) {
				delete (*it);
				it = mob->erase(it);
			}else {
				++it;
			}
			
		}

		bool erease;
		for (std::list<Bullet>::iterator it = bullet->begin(); it != bullet->end(); ) {
			erease = it->update(frametime, mob);
			if (erease) {
				it = bullet->erase(it);
			}else {
				++it;
			}
		}

		


		float playertempxmin = player.getPlayerPosX() - (1600 / 2);
		float playertempxmax = player.getPlayerPosX() + (1600 / 2);

		float playertempymin = player.getPlayerPosY() - (900 / 2);
		float playertempymax = player.getPlayerPosY() + (900 / 2);

		float xmap = player.getPlayerPosX();
		float ymap = player.getPlayerPosY();


		if (playertempxmin < 0) {
			xmap = (1600 / 2);
		}
		if (playertempxmax > Maploader::getMapXSize() * 64 || Maploader::getMapXSize() * 64 < 1630) {
			xmap = (Maploader::getMapXSize() * 64) - (1600 / 2);
		}
		 if (playertempymin < 0) {
			 ymap = (900 / 2);
		 }
		 if (playertempymax > Maploader::getMapYSize() * 64 || Maploader::getMapYSize() * 64 < 930) {
			 ymap = (Maploader::getMapYSize() * 64) - (900 / 2);
		 }
		
		 view->setCenter(xmap-32, ymap-32);

		hptext->setOrigin(sf::Vector2f(hptext->getLocalBounds().width / 2, hptext->getLocalBounds().height));
		hptext->setPosition(player.getPlayerPosX(), player.getPlayerPosY() - 48);
		
	}else {
		guimanager->update(Window);
	}
}


//EVENT METHOD
void Framework::eventhandle() {
	while (Window->pollEvent(*Event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			guimanager->setGuiNumber(1);
		}

		static int sperr = 0;
		bool change = false;
		if (sperr <= 0) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
				mapglobalcords.y--;
				change = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) {
				player.setPos(player.getPlayerPosX() + 128, player.getPlayerPosY());
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
				mapglobalcords.x--;
				change = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
				mapglobalcords.x++;
				change = true;
			}
		}
		sperr--;

		if (change) {
			sperr = 3;
			std::string mapstr = "map." + std::to_string(mapglobalcords.x) + "." + std::to_string(mapglobalcords.y) + ".sean";
			Maploader::destroy();
			Maploader::load(mapstr);
			Maploader::create(up);
			change = false;
			std::cout << mapstr << std::endl;
		}
	}
}


//DRAW METHOD
void Framework::draw() {
	Window->clear();



	if (guimanager->getGuiNumber() == 0) {
		Window->setView(*view);

		for (std::vector<Block*>::iterator it = onlyDrawBlocks->begin(); it != onlyDrawBlocks->end(); ++it) {
			Window->draw(*(*it)->getImage());
		}

		for (std::vector<Block*>::iterator it = updateDrawBlocks->begin(); it != updateDrawBlocks->end(); ++it) {
			Window->draw(*(*it)->getImage());
		}

		for (std::vector<Block*>::iterator it = notCollidingBlocks->begin(); it != notCollidingBlocks->end(); ++it) {
			Window->draw(*(*it)->getImage());
		}


		for (std::list<Bullet>::iterator it = bullet->begin(); it != bullet->end(); ++it) {
			Window->draw(it->getImage());
		}


		for (int i = 0; i < mob->size(); i++) {
			Window->draw(*(*mob)[i]->getImage());
			Window->draw(*(*mob)[i]->getHpBar());
		}

		Window->draw(*player.getImageDraw());

	//	Window->draw(*player.getLasser(0));
	//	Window->draw(*player.getLasser(1));
	//	Window->draw(*player.getLasser(2));

		

		if(player.getShieldHp() > 0)Window->draw(*player.getShieldImage());
		Window->draw(*hptext);

	}else {
		Window->setView(*guiview);
		guimanager->draw(Window);
	}
	
	Window->display();
}


//OTHER STUFF
void Framework::setrunning(bool run){
	running = run;
}
bool Framework::getrunning(){
	return running;
}

void Framework::setPlayerHp(int hp) {
	player.setHp(hp);
}


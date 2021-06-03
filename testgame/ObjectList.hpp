#pragma once
#include <SFML\Graphics.hpp>
#include "MapTrigger.hpp"
#include "Bullet.hpp"
#include "Mob.hpp"
#include <list>

sf::RenderWindow *Window = new sf::RenderWindow(sf::VideoMode(1600, 900, 32), "Game", sf::Style::Titlebar);
sf::Event *Event = new sf::Event;;
sf::Font *font = new sf::Font();;
sf::Text *hptext = new sf::Text("NULL", (*font), 20);;
Maploader *maploader = new Maploader;;
std::vector<MapTrigger> *trigger = new std::vector<MapTrigger>;;
std::list<Bullet> *bullet = new std::list<Bullet>;;
std::list<Mob> *mob = new std::list<Mob>;;
std::vector<Block> *block = new std::vector<Block>;;
int mapy;
int mapx;

class ObjectList {
public:

	 ObjectList() {
		 
		 
		 
	 }
};
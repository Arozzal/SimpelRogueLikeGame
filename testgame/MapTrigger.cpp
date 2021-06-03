#include "MapTrigger.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include "Framework.hpp"
#include "ListManager.hpp"

#include <list>
#include <vector>

extern Player player;


int MapTrigger::counter = 0;

void MapTrigger::update(float frametime){

	if (counter < 0) {
		if (Collision::BoundingBoxTest(*player.getImage(), *getImage())) {
			std::cout << "dir" << std::endl;
			switch (dir) {
			case up: LM::getGlobalMapCords()->y--; break;
			case down: LM::getGlobalMapCords()->y++; break;
			case left: LM::getGlobalMapCords()->x--; break;
			case right: LM::getGlobalMapCords()->x++; break;
			}
			std::string mapstr = "map"+ std::to_string(*LM::getMapNumber()) +"/map." + std::to_string(LM::getGlobalMapCords()->x) + "." + std::to_string(LM::getGlobalMapCords()->y) + ".sean";
			Direction der = dir;
			Maploader::destroy();
			Maploader::load(mapstr);
			Maploader::create(der);
			std::cout << "Mapstring: " << mapstr << std::endl;
			counter = 100;

		}
	}else {
		counter--;
	}
}

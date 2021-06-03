#include "CollisionSystem.hpp"
#include "Player.hpp"
#include "Maploader.hpp"



extern Player player;

namespace CollSystem {
	Collisiondata colldata;
	
	bool collideSolid(sf::Sprite* object1) {
		

			for (std::vector<Block*>::iterator it = colldata.onlyDrawBlocks->begin(); it != colldata.onlyDrawBlocks->end(); ++it) {
				if (Collision::BoundingBoxTest((*object1), (*(*it)->getImage()))) {

					return true;

				}
			}

			
		for (std::vector<Block*>::iterator it = colldata.updateDrawBlocks->begin(); it != colldata.updateDrawBlocks->end(); ++it) {
			if (Collision::BoundingBoxTest((*object1), (*(*it)->getImage()))) {

				return true;

			}
		}

		if (object1->getPosition().y < 0) {
			return true;
		}else if (object1->getPosition().y > Maploader::getMapYSize() * 64) {
			return true;
		}else if (object1->getPosition().x < 0) {
			return true;
		}else if (object1->getPosition().x > Maploader::getMapXSize() * 64) {
			return true;
		}



		return false;
	}

	bool collideSolidForBullets(sf::Sprite* object1, bool enemy) {
		if (object1->getPosition().y< 0) {
			return true;
		}
		else if (object1->getPosition().y > Maploader::getMapYSize() * 64) { 
			return true;
		}
		else if (object1->getPosition().x < 0) {
			return true;
		}
		else if (object1->getPosition().x > Maploader::getMapXSize() * 64) { 
			return true;
		}
		
		colldata.posobjx = (object1->getPosition().x) / 64;
		colldata.posobjy = (object1->getPosition().y) / 64;

		if (colldata.mapgrid->size() < colldata.posobjx) {
			return true;

		}else if ((*colldata.mapgrid)[colldata.posobjx].size() < colldata.posobjy) {
			return true;

		}else if ((*colldata.mapgrid)[colldata.posobjx][colldata.posobjy] > 1 && (*colldata.mapgrid)[colldata.posobjx][colldata.posobjy] < 10) {
			return true;
		}
		else if (enemy == true) {
			if ((*colldata.mapgrid)[colldata.posobjx + 1][colldata.posobjy    ] > 1 && (*colldata.mapgrid)[colldata.posobjx + 1][colldata.posobjy    ] < 10) return true;
			if ((*colldata.mapgrid)[colldata.posobjx + 1][colldata.posobjy + 1] > 1 && (*colldata.mapgrid)[colldata.posobjx + 1][colldata.posobjy + 1] < 10) return true;
			if ((*colldata.mapgrid)[colldata.posobjx    ][colldata.posobjy + 1] > 1 && (*colldata.mapgrid)[colldata.posobjx    ][colldata.posobjy + 1] < 10) return true;
		}



		return false;
	}







	bool collideEnemy(sf::Sprite* object1) {
		for (std::vector<Mob*>::iterator it = colldata.Moblist->begin(); it != colldata.Moblist->end(); ++it) {
			if (Collision::BoundingBoxTest((*object1), (*(*it)->getImage()))) {

				return true;

			}
		}

		return false;
	}

	bool collidePlayer(sf::Sprite* object1) {
		if (Collision::CircleTest((*object1), (*player.getImage()))) {
			return true;
		}

		return false;
	}

	void set(std::vector<Block*>* onlyDrawBlocks, std::vector<Block*>* updateDrawBlocks, std::vector<Mob*>* Moblist, std::vector<Block*>* onlyupdateBlocks) {
		
		colldata.onlyDrawBlocks = onlyDrawBlocks;
		colldata.updateDrawBlocks = updateDrawBlocks;
		colldata.Moblist = Moblist;
		colldata.onlyupdateBlocks = onlyupdateBlocks;
	}

	void setGrid(std::vector<std::vector<int>>* mapgrid){
		colldata.mapgrid = mapgrid;
	}


}
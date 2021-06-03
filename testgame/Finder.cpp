#include "Finder.hpp"
#include "Player.hpp"
#include "CollisionSystem.hpp"
#include <SFML\Graphics.hpp>

extern Player player;
Finder::Finder() {



}

void Finder::update(float frametime){
	
	playerxfields = ((player.getPlayerPosX() - static_cast<int>(player.getPlayerPosX()) % 64) / 64);
	playeryfields = ((player.getPlayerPosY() - static_cast<int>(player.getPlayerPosY()) % 64) / 64);

	nextSquareX = static_cast<int>(getX()) % 64;
	nextSquareY = static_cast<int>(getY()) % 64;
	


	pos1x = (((getX() + 64) - static_cast<int>(getX()) % 64) / 64);
	pos1y = ((getY() - static_cast<int>(getY()) % 64) / 64);

	pos1x2 = (((getX() + 64) - static_cast<int>(getX()) % 64) / 64);
	pos1y2 = (((getY() + 64) - static_cast<int>(getY()) % 64) / 64);

	pos2x = (((getX() - 64) - static_cast<int>(getX()) % 64) / 64);
	pos2y = ((getY() - static_cast<int>(getY()) % 64) / 64);

	pos3x = ((getX() - static_cast<int>(getX()) % 64) / 64);
	pos3y = (((getY() + 64) - static_cast<int>(getY()) % 64) / 64);

	pos4x = ((getX() - static_cast<int>(getX()) % 64) / 64);
	pos4y = (((getY() - 64) - static_cast<int>(getY()) % 64) / 64);
	
	posNx = ((getX() - static_cast<int>(getX()) % 64) / 64);
	posNy = ((getY() - static_cast<int>(getY()) % 64) / 64);

	closedlist[posNx][posNy] = 777;

	if (mapgrid[pos1x][pos1y] != 01) {
		pos1x += 1000;
		pos1y += 1000;

	}
	if (mapgrid[pos1x2][pos1y2] != 01) {
		pos1x += 1000;
		pos1y += 1000;

	}

	if (mapgrid[pos2x][pos2y] != 01) {
		pos2x += 1000;
		pos2y += 1000;
	}
	if (mapgrid[pos3x][pos3y] != 01) {
		pos3x += 1000;
		pos3y += 1000;
	}
	if (mapgrid[pos4x][pos4y] != 01) {
		pos4x += 1000;
		pos4y += 1000;
	}


	pos1x = pos1x - playerxfields;
	pos1y = pos1y - playeryfields;
		
	pos1x2 = pos1x2 - playerxfields;
	pos1y2 = pos1y2 - playeryfields;

	pos2x = pos2x - playerxfields;
	pos2y = pos2y - playeryfields;
		 
	pos3x = pos3x - playerxfields;
	pos3y = pos3y - playeryfields;
		
	pos4x = pos4x - playerxfields;
	pos4y = pos4y - playeryfields;

	

	if (pos1x < 0) {
		pos1x -= pos1x * 2;
	}
	if (pos2x < 0) {
		pos2x -= pos2x * 2;
	}
	if (pos3x < 0) {
		pos3x -= pos3x * 2;
	}
	if (pos4x < 0) {
		pos4x -= pos4x * 2;
	}
	if (pos1y < 0) {
		pos1y -= pos1y * 2;
	}
	if (pos2y < 0) {
		pos2y -= pos2y * 2;
	}
	if (pos3y < 0) {
		pos3y -= pos3y * 2;
	}
	if (pos4y < 0) {
		pos4y -= pos4y * 2;
	}
	pos1 = pos1x + pos1y;
	pos2 = pos2x + pos2y;
	pos3 = pos3x + pos3y;
	pos4 = pos4x + pos4y;

	Direction dire = smallest(pos1, pos2, pos3, pos4);

	float posxnow = getX();
	float posynow = getY();


	switch (dire) {
	case Direction::right:
		setPosition((getX() + (64 * frametime)), (getY() + (0 * frametime)));
		break;
	case Direction::left:
		setPosition((getX() + (-64 * frametime)), (getY() + (0 * frametime)));
		break;
	case Direction::down:
		setPosition((getX() + (0 * frametime)), (getY() + (64 * frametime)));
		break;
	case Direction::up:
		setPosition((getX() + (0 * frametime)), (getY() + (-64 * frametime)));
		break;
	}
	
	/*if (CollSystem::collideSolid(getImage())) {
		setPosition(posxnow, posynow);
	}*/
	lastdir = dir;

	std::cout << pos1 << " "<< pos2 <<  " "<< pos3 << " " << pos4 << " x1: " <<  dire << std::endl;
}


Direction Finder::smallest(int i1, int i2, int i3, int i4) {
	unusablei1 = false;
	unusablei2 = false;
	unusablei3 = false;
	unusablei4 = false;
	if ((closedlist[posNx + 1][posNy] == 777) || (pos1x >= 500)) {
		unusablei1 = true;
	}else if ((closedlist[posNx + 1][posNy+1] == 777) || (pos1x2 >= 500)) {
		unusablei1 = true;
	}

	if ((closedlist[posNx - 1][posNy] == 777) || (pos1x >= 500)) {
		unusablei2 = true;
	}
	if ((closedlist[posNx][posNy + 1] == 777) || (pos1y >= 500)) {
		unusablei3 = true;
	}

	if ((closedlist[posNx][posNy - 1] == 777) || (pos1y >= 500)) {
		unusablei4 = true;
	}else if ((closedlist[posNx][posNy + 1] == 777) || (pos1y >= 500)) {
		unusablei4 = true;
	}



		if ((i1 <= i2 || unusablei2)  && (i1 <= i3 || unusablei3) && (i1 <= i4 || unusablei4) && (closedlist[posNx+1][posNy] != 777) && (mapgrid[posNx + 1][posNy] == 01)) {
			std::cout << closedlist[pos1x][pos1y] << std::endl;
			return Direction::right;

		}else if ((i2 <= i1 || unusablei1) && (i2 <= i3 || unusablei3) && (i2 <= i4 || unusablei4) && (closedlist[posNx-1][posNy] != 777) && (mapgrid[posNx - 1][posNy] == 01)){
			std::cout << closedlist[pos2x][pos2y] << std::endl;
			return Direction::left;

		}else if ((i3 <= i2 || unusablei2) && (i3 <= i1 || unusablei1) && (i3 <= i4 || unusablei4) && (closedlist[posNx][posNy+1] != 777) && (mapgrid[posNx][posNy + 1] == 01)){
			std::cout << closedlist[pos3x][pos3y] << std::endl;
			return Direction::down;

		}else if ((i4 <= i2 || unusablei2) && (i4 <= i3 || unusablei3) && (i4 <= i1 || unusablei1) && (closedlist[posNx][posNy-1] != 777) && (mapgrid[posNx][posNy - 1] == 01)){
			std::cout << closedlist[pos4x][pos4y] << std::endl;
			return Direction::up;

		}else {
			if (!unusablei1) {
				return Direction::right;
			}
			if (!unusablei2) {
				return Direction::left;
			}if (!unusablei3) {
				return Direction::down;
			}if (!unusablei4) {
				return Direction::up;
			}else {
				for (int i = 0; i < closedlist.size(); i++) {
					for (int d = 0; d < closedlist[i].size(); d++) {
						closedlist[i][d] = 01;
					}
				}
				return Null;
			}
		}

}
#pragma once
#include "Mob.hpp"

class Finder : public Mob {
public:
	Finder();
	void update(float) override;
	Direction smallest(int, int, int, int);
private:
	int playerxfields;
	int playeryfields;
	int selfxfields;
	int selfyfields;
	int blockstoend;
	int tox;
	int toy;
	int fieldstoplayer;
	int posNx;
	int posNy;

	int pos1x2;
	int pos1y2;

	float nextSquareX;
	float nextSquareY;
	Direction lastdir = Direction::Null;

	bool unusablei1 = false;
	bool unusablei2 = false;
	bool unusablei3 = false;
	bool unusablei4 = false;

	int myposx;
	int myposy;

	int pos1x;
	int pos2x;
	int pos3x;
	int pos4x;

	bool iscollided = true;

	int pos1y;
	int pos2y;
	int pos3y;
	int pos4y;

	int pos1;
	int pos2;
	int pos3;
	int pos4;


	int count;
};
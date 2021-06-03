#pragma once
#include "Block.hpp"
#include <SFML\Graphics.hpp>

class Mob : public Block{
private:
	
	int hp;
	
	sf::Text hptext;
	sf::Font hpfont;
	
public:
	
	int getHp();
	void setHp(int);
	void setMapgrid(std::vector<std::vector<int>>);
	sf::Text* getHpBar();
	void setart(int);
	Mob();
	Direction getNextDir(Direction);
	void virtual update(float frametime) = 0;

	virtual ~Mob() {};
protected:
	int art = 0;
	std::vector<std::vector<int>> openlist;
	std::vector<std::vector<int>> closedlist;
	std::vector<std::vector<int>> mapgrid;
};
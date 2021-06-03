#pragma once
#include <SFML\Graphics.hpp>

enum Color {
	BLACK,
	WHITE,
	RED,
	LIME,
	BLUE,
	YELLOW,
	CYAN,
	MAGNETA,
	SILVER,
	GRAY,
	MARRON,
	OLIVE,
	GREEN,
	PURPLE,
	TEAL,
	NAVY,
	INVISIBLE
};
enum Direction {
	right,
	left,
	up,
	down,
	Null
};

class Block{
protected:
	float beginypos;
	Direction dir;

	sf::Vector2i Ids;

	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	float posx;
	float posy;
	float sizex;
	float sizey;

public:
	void setDirection(Direction);
	sf::Sprite *getImage();
	void setSize(float sizex, float sizey);
	void setPosition(float posx, float posy);
	void create(float sizex,float sizey);
	void create(sf::String);
	void setColor(Color);
	virtual void update(float);
	float getX();
	float getY();
	void addItemPickupContainer(sf::Vector2i);
	float getSize();
	void setIds(int x, int y) { Ids.x = x; Ids.y = y; };
	sf::Vector2i getIds() { return Ids; };
	Block();
};
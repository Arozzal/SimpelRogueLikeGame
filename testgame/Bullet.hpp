#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Mob.hpp"
#include "Ghost.hpp"
#include <list>



class Bullet {
private:
	float posx;
	float posy;
	int temphp;
	float bulletspeed = 150;
	bool friendly = true;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f bulletangle;

	

public:
	Bullet(float,float,float, sf::Vector2f,float,bool friendly);
	void setColor(sf::Color);
	bool update(float frametime,std::vector<Mob*>*);
	sf::Sprite getImage();
	unsigned int getSize();
};
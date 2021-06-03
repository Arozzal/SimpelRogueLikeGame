#pragma once
#include <SFML\Graphics.hpp>
#include "Block.hpp"
#include <iostream>
#include "Collision.hpp"
#include "Framework.hpp"
#include "Event.hpp"
#include "Block.hpp"
#include "Bullet.hpp"
#include <list>

class Player{
private:
	sf::Image  image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Image  imagefake;
	sf::Texture texturefake;
	sf::Sprite spritefake;
	float bulletcolldownstat = 25;
	sf::Vector2f pos;
	sf::Vector2i size;

	sf::VertexArray lasser[3] = {};
	sf::CircleShape lassercircle[3] = {};

	sf::Image shieldimage;
	sf::Texture shieldtexture;
	sf::Sprite shieldsprite;

	int shieldHp;

	int BulletCountAtShot = 1;
	float Bulletspeed = 300;
	float speed = 150;
	const int BULLETSIZE = 32;
	int hp;
	float dmgcolldowncount;
	bool dmgcolldown = false;
	float Radian;
	float Degree;

public:
	Player(float x, float y, int xsize, int ysize);
	sf::Sprite *getImage();
	sf::Sprite* getImageDraw();
	sf::Sprite* getShieldImage();
	void setPos(float, float);
	void update(float frametime, std::list<Bullet>*, float y = 0, float x = 0);
	float getPlayerPosX();
	float getPlayerPosY();
	void doDmg(int);
	int getHp();
	void setHp(int);
	sf::Vector2f getPlayerPos();
	sf::VertexArray* getLasser(int num)  { return &lasser[num]; };
	sf::CircleShape* getLasserCircle(int num) { return &lassercircle[num]; };

	float getSpeed(); 
	void setSpeed(float);
	float getColldown();
	void setColldown(float);
	float getBulletSpeed();
	void setBulletSpeed(float);
	void addBulletCountAtShot();
	void setShieldHp(int);
	int getShieldHp();
};
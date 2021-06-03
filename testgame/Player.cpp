#include <SFML\Graphics.hpp>
#include <iostream>
#include <math.h>




#include "Player.hpp"
#include "Event.hpp"
#include "Bullet.hpp"
#include "Block.hpp"
#include "Collision.hpp"
#include "Mob.hpp"
#include "CollisionSystem.hpp"
#include "ListManager.hpp"


	Player::Player(float x, float y, int xsize, int ysize) {
		dmgcolldowncount = 0;
		hp = 100;
		shieldHp = 0;

		image.loadFromFile("images/Player.png"); imagefake.loadFromFile("images/Player.png");
		texture.loadFromImage(image); texturefake.loadFromImage(image);
		sprite.setTexture(texture); spritefake.setTexture(texture);
		
		shieldimage.loadFromFile("images/Shield.png");
		shieldtexture.loadFromImage(shieldimage);
		shieldsprite.setTexture(shieldtexture);

		/*lasser[0].setSize(sf::Vector2f(20, 600));
		lasser[0].setFillColor(sf::Color::Blue);
		lasser[0].setOrigin(sf::Vector2f(10, 600));

		lasser[1].setSize(sf::Vector2f(10, 600));
		lasser[1].setFillColor(sf::Color::Cyan);
		lasser[1].setOrigin(sf::Vector2f(5, 600));
			  
		lasser[2].setSize(sf::Vector2f(5, 600));
		lasser[2].setFillColor(sf::Color::White);
		lasser[2].setOrigin(sf::Vector2f(2.5, 600));*/

		lasser[0].setPrimitiveType(sf::PrimitiveType::Points);
		lasser[0].resize(4);

		lassercircle[0].setPointCount(3);
		lassercircle[0].setRadius(20);
		lassercircle[0].setFillColor(sf::Color::Blue);
		lassercircle[0].setOrigin(sf::Vector2f(lassercircle[0].getRadius() , lassercircle[0].getRadius() ));

		lassercircle[1].setPointCount(3);
		lassercircle[1].setRadius(15);
		lassercircle[1].setFillColor(sf::Color::Cyan);
		lassercircle[1].setOrigin(sf::Vector2f(lassercircle[1].getRadius() , lassercircle[1].getRadius() ));

		lassercircle[2].setPointCount(3);
		lassercircle[2].setRadius(7);
		lassercircle[2].setFillColor(sf::Color::White);
		lassercircle[2].setOrigin(sf::Vector2f(lassercircle[2].getRadius() , lassercircle[2].getRadius() ));

		shieldsprite.setOrigin(sf::Vector2f(shieldimage.getSize().x / 2, shieldimage.getSize().y));

		pos.x = x;
		pos.y = y;
		size.x = xsize;
		size.y = ysize;
		sprite.setOrigin(image.getSize().x/2, image.getSize().y / 2); spritefake.setOrigin(image.getSize().x / 2, image.getSize().y / 2);
	}

	void Player::setPos(float xpos, float ypos) {
		sprite.setPosition(xpos, ypos);
		spritefake.setPosition(xpos, ypos);
	}
	

	void Player::update(float frametime, std::list<Bullet>* bullet, float y, float x) {
		static bool theoreother = false;
		static int bulletcolldown = 0;

		sf::Vector2i mouse = static_cast<sf::Vector2i>(LM::getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*LM::getWindow())));
		mouse -= static_cast<sf::Vector2i>(sprite.getPosition());
		Radian = std::atan2(mouse.y, mouse.x);
		Degree = (Radian * 180 / 3.141);


		sprite.setRotation(Degree+90);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (bulletcolldown <= 0)) {
			bulletcolldown = bulletcolldownstat;
			sf::Vector2f bulletangle(std::cos(Radian), std::sin(Radian));
			
			switch (BulletCountAtShot) {
			case 1:
				bullet->emplace_back(Bulletspeed, getPlayerPosX(), getPlayerPosY(), bulletangle, Degree + 90, true);
				break;
			case 2:
				bullet->emplace_back(Bulletspeed, getPlayerPosX() + (bulletangle.y * 15), getPlayerPosY() - (bulletangle.x * 15), bulletangle, Degree + 90, true);
				bullet->emplace_back(Bulletspeed, getPlayerPosX() - (bulletangle.y * 15), getPlayerPosY() + (bulletangle.x * 15), bulletangle, Degree + 90, true);
				break;
			case 3:
				bullet->emplace_back(Bulletspeed, getPlayerPosX() + (bulletangle.y * 30), getPlayerPosY() - (bulletangle.x * 30), bulletangle, Degree + 90, true);
				bullet->emplace_back(Bulletspeed, getPlayerPosX(), getPlayerPosY(), bulletangle, Degree + 90, true);
				bullet->emplace_back(Bulletspeed, getPlayerPosX() - (bulletangle.y * 30), getPlayerPosY() + (bulletangle.x * 30), bulletangle, Degree + 90, true);
				break;
			}
		}

		if (!x && !y) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
				y += speed;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
				y += -speed;
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
				x += speed;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
				x += -speed;
			}
		}
		
		dmgcolldowncount--;
		bool collx = false;
		bool colly = false;

		if (bulletcolldown > 0) {
			bulletcolldown--;
		}


		sprite.move(x*frametime,0); spritefake.move(x*frametime, 0);

		if (CollSystem::collideSolid(&spritefake)) {
			collx = true;
		}
		sprite.move(-x*frametime, 0); spritefake.move(-x*frametime, 0);

		sprite.move(0, y*frametime); spritefake.move(0, y*frametime);

		if (CollSystem::collideSolid(&spritefake)) {
			colly = true;
		}

		sprite.move(0, -y*frametime); spritefake.move(0, -y*frametime);

		if (collx == false) {
			if (x) {
				pos.x = x;
			}
		}
			if (colly == false) {
				if (y) {
					pos.y = y;
				}
			}
		

		this->sprite.move(pos.x*frametime, pos.y*frametime); this->spritefake.move(pos.x*frametime, pos.y*frametime);
		shieldsprite.setPosition(sprite.getPosition().x+std::cos(Radian)*image.getSize().x / 2,sprite.getPosition().y+std::sin(Radian)*image.getSize().x/2);
		shieldsprite.setRotation(Degree+90);

		pos.x = 0;
		pos.y = 0;
		/*
		float cos = std::cos(Radian);
		float sin = std::sin(Radian);
		float imagexsize = image.getSize().x / 2;
		float imageysize = image.getSize().y / 2;

		sf::Vector2f rotpoint(cos * imagexsize + sprite.getPosition().x, sprite.getPosition().y + sin*imageysize);


	/*	lasser[0][0].position = sf::Vector2f(rotpoint.x + cos * 30, rotpoint.y + sin * 20);
		lasser[0][1].position = sf::Vector2f(cos * imagexsize + sprite.getPosition().x , sprite.getPosition().y + sin*imageysize);
		lasser[0][2].position = sf::Vector2f(cos * imagexsize + sprite.getPosition().x , sprite.getPosition().y + sin*imageysize);
		lasser[0][3].position = sf::Vector2f(cos * imagexsize + sprite.getPosition().x , sprite.getPosition().y +   sin*imageysize);*/
		/*lasser[0].setRotation(Degree + 90);
	//	lasser[0].setTextureRect(sf::IntRect(sf::Vector2f(sprite.getPosition().x + std::cos(Radian)*image.getSize().x / 2, sprite.getPosition().y + std::sin(Radian)*image.getSize().x / 2)));
		lasser[0].setPosition;
			 
		lasser[1].setRotation(Degree + 90);
		lasser[1].setPosition(sprite.getPosition().x + std::cos(Radian)*image.getSize().x / 2, sprite.getPosition().y + std::sin(Radian)*image.getSize().x / 2);
			
		lasser[2].setRotation(Degree + 90);
		lasser[2].setPosition(sprite.getPosition().x + std::cos(Radian)*image.getSize().x / 2, sprite.getPosition().y + std::sin(Radian)*image.getSize().x / 2);*/

		lassercircle[0].setPosition(sprite.getPosition().x + std::cos(Radian)*image.getSize().x / 1.5, sprite.getPosition().y + std::sin(Radian)*image.getSize().x / 1.5);
		
		lassercircle[1].setPosition(sprite.getPosition().x + std::cos(Radian)*image.getSize().x / 1.5, sprite.getPosition().y + std::sin(Radian)*image.getSize().x / 1.5);
			
		lassercircle[2].setPosition(sprite.getPosition().x + std::cos(Radian)*image.getSize().x / 1.5, sprite.getPosition().y + std::sin(Radian)*image.getSize().x / 1.5);

	}



	float Player::getPlayerPosX() {
		sf::Vector2f tempvec = spritefake.getPosition();
		float cx = tempvec.x;
		return cx;
	}
	float Player::getPlayerPosY() {
		sf::Vector2f tempvec = spritefake.getPosition();
		float cy = tempvec.y;
		return cy;
	}

	void Player::doDmg(int dmgnumber){
		if (dmgcolldowncount <= 0) {
			dmgcolldown = false;
		}

		if (!dmgcolldown) {
			hp -= dmgnumber;
			dmgcolldowncount = 50;
			dmgcolldown = true;
		}
	}

	int Player::getHp(){
		return hp;
	}

	void Player::setHp(int hp) {
		this->hp = hp;
	}

	sf::Vector2f Player::getPlayerPos() {
		return spritefake.getPosition();
	}

	float Player::getSpeed(){
		return this->speed;
	}

	void Player::setSpeed(float speed){
		this->speed = speed;
	}
	float Player::getColldown() {
		return this->bulletcolldownstat;
	}

	void Player::setColldown(float colldown) {
		this->bulletcolldownstat = colldown;
	}

	float Player::getBulletSpeed(){
		return Bulletspeed;
	}

	void Player::setBulletSpeed(float bulletspeed){
		this->Bulletspeed = bulletspeed;
	}

	void Player::addBulletCountAtShot(){
		if (BulletCountAtShot < 3) {
			BulletCountAtShot++;
		}
	}

	void Player::setShieldHp(int hp){
		shieldHp = hp;
	}

	int Player::getShieldHp(){
		return shieldHp;
	}

	sf::Sprite* Player::getImage() {
		return &spritefake;
	}

	sf::Sprite* Player::getImageDraw() {
		return &sprite;
	}

	sf::Sprite * Player::getShieldImage()
	{
		return &shieldsprite;
	}

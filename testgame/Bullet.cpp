#include "Bullet.hpp"
#include "Mob.hpp"
#include "Collision.hpp"
#include <vector>
#include <iostream>
#include "Ghost.hpp"
#include <list>

#include "Player.hpp"
#include "CollisionSystem.hpp"

extern Player player;

Bullet::Bullet(float bulletspeed ,float posx, float posy, sf::Vector2f bulletangle, float degree, bool friendly){

	this->friendly = friendly;
	this->bulletspeed = bulletspeed;

	if (friendly) {
		this->image.loadFromFile("images/Bullet_Player.png");
	}else {		   
		this->image.loadFromFile("images/Bullet_Enemy.png");
	}
	this->texture.loadFromImage(image);
	this->sprite.setTexture(texture);
	this->sprite.setPosition(posx, posy);
	this->bulletangle = bulletangle;

	this->sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

	this->sprite.setRotation(degree);
}

void Bullet::setColor(sf::Color col){
	sprite.setColor(col);
}



bool Bullet::update(float frametime, std::vector<Mob*>* mob){


	this->sprite.move(sf::Vector2f(bulletangle.x * frametime * bulletspeed, bulletangle.y * frametime * bulletspeed));


	if (friendly) {
		for (std::vector<Mob*>::iterator it = mob->begin(); it != mob->end(); ++it) {
			if (Collision::BoundingBoxTest(sprite, (*(*it)->getImage()))) {
				temphp = (*it)->getHp();
				temphp--;
				(*it)->setHp(temphp);
				return true;
			}
		}
	}else {
		if (Collision::BoundingBoxTest(sprite, *player.getShieldImage()) && player.getShieldHp() > 0) {
			player.setShieldHp(player.getShieldHp() - 25);
			return true;
		}
		if (Collision::CircleTest(sprite, *player.getImage())) {
			player.doDmg(5);
			return true;
		}
	}




	this->sprite.setPosition(sprite.getPosition().x+32, sprite.getPosition().y+32);
	if (CollSystem::collideSolidForBullets(&sprite)) {
		return true;
	}
	this->sprite.setPosition(sprite.getPosition().x - 32, sprite.getPosition().y - 32);

	
	return false;
}

sf::Sprite Bullet::getImage(){
	return (sprite);
}



unsigned int Bullet::getSize() {

	return image.getSize().y;
}


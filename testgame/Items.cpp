#include "Items.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include "Maploader.hpp"
#include <chrono>


extern Player player;

void SpeedItem::update(float){
	if (Collision::CircleTest(*player.getImage(), *getImage())) {
		player.setSpeed(player.getSpeed() + 40);
		setPosition(-10000.f, -10000.f);
		addItemPickupContainer(Ids);
	}else {
		itemAnimation();
	}
}


void BulletUpgradeItem::update(float){
	if (Collision::CircleTest(*player.getImage(), *getImage())) {
		player.setColldown(player.getColldown() * 0.7);
		setPosition(-10000.f, -10000.f);
		addItemPickupContainer(Ids);
	}else {
		itemAnimation();
	}
}



void BulletSpeedUpgradeItem::update(float) {
	if (Collision::CircleTest(*player.getImage(), *getImage())) {
		player.setBulletSpeed(player.getBulletSpeed() + 100);
		setPosition(-10000.f, -10000.f);
		addItemPickupContainer(Ids);
	}else {
		itemAnimation();
	}
}

void BulletAtShotUpgradeItem::update(float){
	if (Collision::CircleTest(*player.getImage(), *getImage())) {
		player.addBulletCountAtShot();
		setPosition(-10000.f, -10000.f);
		addItemPickupContainer(Ids);
	}else {
		itemAnimation();
	}
}

void ShieldUpgradeItem::update(float){
	if (Collision::CircleTest(*player.getImage(), *getImage())) {
		player.setShieldHp(100);
		setPosition(-10000.f, -10000.f);
		addItemPickupContainer(Ids);
	}else {
		itemAnimation();
	}
}

void Item::itemAnimation(){
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	double millis = std::chrono::duration_cast<std::chrono::milliseconds>(ms).count();

	double yyy = std::sin(millis * 0.001) * 0.5;
	
	yyy = abs(yyy);

	yyy += 0.5;
	yyy *= 0.5;
	yyy += 0.5;

	sprite.setScale(yyy, yyy);
}

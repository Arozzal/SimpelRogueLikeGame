#pragma once
#include "Block.hpp"

class Item : public Block {
public:
	void itemAnimation();
};

class SpeedItem : public Item {
	void update(float) override;
};

class BulletUpgradeItem : public Item {
public:
	void update(float) override;
};

class BulletSpeedUpgradeItem : public Item {
	void update(float) override;
};

class BulletAtShotUpgradeItem : public Item {
	void update(float) override;
};

class ShieldUpgradeItem : public Item {
	void update(float) override;
};
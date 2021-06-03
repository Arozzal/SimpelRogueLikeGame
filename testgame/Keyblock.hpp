#pragma once
#include "Block.hpp"


class Keyblock : public Block{
public:
	void update(float) override;
	static bool getLocked();
	static void setLocked(bool);
private:
	static bool locked;
};
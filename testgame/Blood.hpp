#pragma once
#include "Block.hpp"


class Blood : public Block {
public:
	void update(float);
	static void Blood::thirdplus();
private:
	static int third;
};
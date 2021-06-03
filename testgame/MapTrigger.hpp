#pragma once
#include <vector>
#include <list>
#include "Block.hpp"


class MapTrigger : public Block{
private:
	
	static int counter;
public:
	void update(float) override;

};
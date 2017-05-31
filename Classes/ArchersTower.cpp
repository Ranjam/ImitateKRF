#include "ArchersTower.h"



ArchersTower::ArchersTower() {
}


ArchersTower::~ArchersTower() {
}

bool ArchersTower::init() {
	if (!BaseTower::init()) {
		return false;
	}

	return true;
}

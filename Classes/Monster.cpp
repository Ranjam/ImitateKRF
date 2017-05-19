#include "Monster.h"



Monster::Monster() {
}


Monster::~Monster() {
}

bool Monster::initMonster(int type, int road, int path) {
	this->type = type;
	this->road = road;
	this->path = path;
	return true;
}

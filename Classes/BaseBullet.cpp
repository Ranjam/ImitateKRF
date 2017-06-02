#include "BaseBullet.h"



BaseBullet::BaseBullet() {
}


BaseBullet::~BaseBullet() {
}

bool BaseBullet::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}

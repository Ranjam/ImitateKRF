#include "ArrowBullet.h"



ArrowBullet::ArrowBullet() {
}


ArrowBullet::~ArrowBullet() {
}

bool ArrowBullet::init() {
	if (!BaseBullet::init()) {
		return false;
	}

	this->power_ = 10.0f;

	this->initWithSpriteFrameName("arrow.png");
	this->setFlippedX(true);

	return true;
}

void ArrowBullet::attack() {
	this->runAction(Sequence::create(bullet_animation_, 
									 CallFunc::create(CC_CALLBACK_0(ArrowBullet::destroy, this)),
									 NULL));
}

void ArrowBullet::destroy() {
	this->removeFromParentAndCleanup(true);
}

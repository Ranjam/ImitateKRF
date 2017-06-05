#include "RangeCircle.h"



RangeCircle::RangeCircle() {
}


RangeCircle::~RangeCircle() {
}

bool RangeCircle::init(RangeType type, unsigned int scope) {
	if (!Sprite::init()) {
		return false;
	}

	auto left_top = Sprite::createWithSpriteFrameName("rally_circle.png");
	left_top->setAnchorPoint(Vec2(1, 0));
	this->addChild(left_top);

	auto right_top = Sprite::createWithSpriteFrameName("rally_circle.png");
	right_top->setFlippedX(true);
	right_top->setAnchorPoint(Vec2(0, 0));
	this->addChild(right_top);

	auto left_down = Sprite::createWithSpriteFrameName("rally_circle.png");
	left_down->setAnchorPoint(Vec2(1, 1));
	left_down->setFlippedY(true);
	this->addChild(left_down);

	auto right_down = Sprite::createWithSpriteFrameName("rally_circle.png");
	right_down->setAnchorPoint(Vec2(0, 1));
	right_down->setFlippedX(true);
	right_down->setFlippedY(true);
	this->addChild(right_down);

	// set the scope
	this->setScale(scope / left_top->getContentSize().width);

	return true;
}

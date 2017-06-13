#include "RangeCircle.h"



RangeCircle::RangeCircle() {
}


RangeCircle::~RangeCircle() {
}

bool RangeCircle::init(RangeType type, unsigned int scope) {
	if (!Sprite::init()) {
		return false;
	}
	//range_circle.png
	std::string png_name;
	if (type == RangeType::RALLY) {
		png_name = "rally_circle.png";
	} else {
		png_name = "range_circle.png";
	}

	auto left_top = Sprite::createWithSpriteFrameName(png_name);
	left_top->setAnchorPoint(Vec2(1, 0));
	this->addChild(left_top);

	auto right_top = Sprite::createWithSpriteFrameName(png_name);
	right_top->setFlippedX(true);
	right_top->setAnchorPoint(Vec2(0, 0));
	this->addChild(right_top);

	auto left_down = Sprite::createWithSpriteFrameName(png_name);
	left_down->setAnchorPoint(Vec2(1, 1));
	left_down->setFlippedY(true);
	this->addChild(left_down);

	auto right_down = Sprite::createWithSpriteFrameName(png_name);
	right_down->setAnchorPoint(Vec2(0, 1));
	right_down->setFlippedX(true);
	right_down->setFlippedY(true);
	this->addChild(right_down);

	// set the scope
	this->setScale(scope / left_top->getContentSize().width);

	return true;
}

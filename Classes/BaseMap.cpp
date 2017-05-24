#include "BaseMap.h"



BaseMap::BaseMap() {
}


BaseMap::~BaseMap() {
}

bool BaseMap::init(int level) {
	if (!Layer::init()) {
		return false;
	}

	// add map
	map_ = Sprite::createWithSpriteFrameName(StringUtils::format("Stage_%d.png", level));
	map_->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(map_, 0);

	return true;
}

const Size& BaseMap::getContentSize() const {
	return map_->getContentSize();
}

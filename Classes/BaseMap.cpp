#include "BaseMap.h"
#include "Common.h"


BaseMap::BaseMap() {
}


BaseMap::~BaseMap() {
}

bool BaseMap::init(int level) {
	
	if (!Layer::init()) {
		return false;
	}

	// add map
	auto sprite_map = Sprite::createWithSpriteFrameName(StringUtils::format("Stage_%d.png", level));
	sprite_map->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(sprite_map, 0);
	// on moved
	auto touch_move_listener = EventListenerTouchOneByOne::create();
	touch_move_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		return true;
	};

	touch_move_listener->onTouchMoved = [=](Touch *touch, Event *event) {
		auto targetPostion = sprite_map->getPosition() + touch->getDelta();
		targetPostion.x = MIN(0, targetPostion.x);
		targetPostion.x = MAX(winSize.width - sprite_map->getContentSize().width, targetPostion.x);
		targetPostion.y = MIN(0, targetPostion.y);
		targetPostion.y = MAX(winSize.height - sprite_map->getContentSize().height, targetPostion.y);
		sprite_map->setPosition(targetPostion);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_move_listener, sprite_map);
	return true;
}

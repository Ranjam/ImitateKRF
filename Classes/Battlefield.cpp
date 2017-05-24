#include "Battlefield.h"
#include "Common.h"

Battlefield::Battlefield() {
}


Battlefield::~Battlefield() {
}

bool Battlefield::init(int level) {
	
	if (!Layer::init()) {
		return false;
	}

	// map
	map_ = BaseMap::create(level);
	map_->setAnchorPoint(Vec2(0, 0));
	this->addChild(map_, -1);

	// monsters
	monster_layer_ = MonsterLayer::create();
	this->addChild(monster_layer_, 1);

	// ui
	battlefield_ui_ = BattlefieldUI::create();
	this->addChild(battlefield_ui_, 2);

	battlefield_ui_->addWarningFlags(winSize.width / 2, winSize.height / 2);

	// on moved
	auto touch_move_listener = EventListenerTouchOneByOne::create();
	touch_move_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		return true;
	};

	touch_move_listener->onTouchMoved = [=](Touch *touch, Event *event) {
		auto targetPostion = this->getPosition() + touch->getDelta();
		targetPostion.x = MIN(0, targetPostion.x);
		targetPostion.x = MAX(winSize.width - map_->getContentSize().width, targetPostion.x);
		targetPostion.y = MIN(0, targetPostion.y);
		targetPostion.y = MAX(winSize.height - map_->getContentSize().height, targetPostion.y);
		this->setPosition(targetPostion);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_move_listener, this);
	return true;
}

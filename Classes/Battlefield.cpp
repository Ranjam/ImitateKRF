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

	schedule(schedule_selector(Battlefield::updateWave), 1 / 60.0f);

	// map
	map_ = BaseMap::create(level);
	map_->setAnchorPoint(Vec2(0, 0));
	this->addChild(map_, -1);

	// monsters
	monster_layer_ = MonsterLayer::create();
	this->addChild(monster_layer_, 1);

	// warning flag
	auto flag = WarningFlag::create();
	flag->setPosition(1085, winSize.height / 2 + 172);
	flag->setSpeed(10);
	this->addChild(flag);
	warning_flags_.pushBack(flag);

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

void Battlefield::updateWave(float dt) {
	for (int i = 0; i < warning_flags_.size(); ++i) {
		if (warning_flags_.at(i)->isOver() && monster_layer_->waveIsOver()) {
			monster_layer_->nextWave(dt);
			unschedule(schedule_selector(Battlefield::updateWave));
			schedule(schedule_selector(Battlefield::updateFlag), dt);
		}
	}
}

void Battlefield::updateFlag(float dt) {
	if (monster_layer_->waveIsOver() && warning_flags_.at(0)->isOver()) {
		warning_flags_.at(0)->start();
		unschedule(schedule_selector(Battlefield::updateFlag));
		schedule(schedule_selector(Battlefield::updateWave));
	}
}


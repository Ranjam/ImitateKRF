#include "Battlefield.h"
#include "Common.h"
#include "Stronghold.h"

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
	map_->setPosition(0, 0);
	this->addChild(map_, -1);

	// monsters
	monster_layer_ = MonsterLayer::create();
	monster_layer_->setAnchorPoint(Vec2(0, 0));
	monster_layer_->setPosition(0, 0);
	this->addChild(monster_layer_, 1);

	// warning flag
	auto flag = WarningFlag::create();
	flag->setPosition(1085, winSize.height / 2 + 172);
	flag->setSpeed(10);
	this->addChild(flag, 2);
	warning_flags_ = flag;

	// stronghold
	auto hold = Stronghold::create();
	hold->setPosition(winSize.width / 2 + 200, winSize.height / 2 + 180);
	this->addChild(hold, 1);

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

#if 0
	// debug to decide point
	touch_move_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		auto point = this->monster_layer_->convertTouchToNodeSpace(touch);
		log("<dict>"
			"<key>x</key>"
			"<string>%g</string>"
			"<key>y</key>"
			"<string>%g</string>"
			"</dict>", 
			point.x, point.y);
	};
#endif

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_move_listener, this);
	return true;
}

void Battlefield::updateWave(float dt) {
	if (monster_layer_->allOver()) {
		unschedule(schedule_selector(Battlefield::updateWave));
		return;
	}
	if (warning_flags_->isOver() && monster_layer_->waveIsOver()) {
		monster_layer_->nextWave();
		unschedule(schedule_selector(Battlefield::updateWave));
		schedule(schedule_selector(Battlefield::updateFlag), dt);
	}
}

void Battlefield::updateFlag(float dt) {
	if (monster_layer_->waveIsOver() && warning_flags_->isOver()) {
		warning_flags_->start();
		unschedule(schedule_selector(Battlefield::updateFlag));
		schedule(schedule_selector(Battlefield::updateWave));
	}
}

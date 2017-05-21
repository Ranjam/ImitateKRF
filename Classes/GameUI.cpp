#include "GameUI.h"

GameUI::GameUI() {
}


GameUI::~GameUI() {
}

bool GameUI::init() {

	if (!Layer::init()) {
		return false;
	}

	// set meteor skill
	setMeteor();

	// select target screen
	select_target_ = EventListenerTouchOneByOne::create();
	select_target_->setSwallowTouches(true);
	select_target_->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		// resume background
		auto meteor_bg = static_cast<Sprite *>(this->getChildByTag(METEOR_BG));
		meteor_bg->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0001.png"));
		// open progress
		auto meteor_prog = this->getChildByTag(METEOR_PROG);
		meteor_prog->setVisible(true);
		schedule(schedule_selector(GameUI::updateMeteor), 1.0f / 30);
		_eventDispatcher->pauseEventListenersForTarget(meteor_prog);
		select_target_->setEnabled(false);
		// close meteor
		on_meteor_ = false;
		return true;
	};
	select_target_->setEnabled(false);
	_eventDispatcher->addEventListenerWithFixedPriority(select_target_, 1);

	return true;
}

void GameUI::setMeteor() {
	// meteor skill backgournd
	auto meteor_bg = Sprite::createWithSpriteFrameName("power_portrait_fireball_0001.png");
	meteor_bg->setAnchorPoint(Vec2(0, 0));
	meteor_bg->setPosition(10, 10);
	this->addChild(meteor_bg, 1);
	meteor_bg->setTag(METEOR_BG);

	// meteor skill progress
	auto meteor_prog = ProgressTimer::create(Sprite::createWithSpriteFrameName("power_loading.png"));
	meteor_prog->setAnchorPoint(Point(0, 0));
	meteor_prog->setReverseDirection(true);
	meteor_prog->setPosition(Point(10, 10));
	meteor_prog->setPercentage(100);
	meteor_prog->setVisible(false);
	this->addChild(meteor_prog, 1);
	meteor_prog->setTag(METEOR_PROG);

	// add meteor skill listener
	auto meteor_listener = EventListenerTouchOneByOne::create();
	// UI swallow event
	meteor_listener->setSwallowTouches(true);

	meteor_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (meteor_prog->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			return true;
		}
		return false;
	};

	meteor_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		if (!on_meteor_) {
			on_meteor_ = true;
			meteor_bg->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0002.png"));
			select_target_->setEnabled(true);
		} else {
			on_meteor_ = false;
			meteor_bg->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0001.png"));
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(meteor_listener, meteor_prog);
}

void GameUI::updateMeteor(float dt) {
	auto meteor_prog = static_cast<ProgressTimer *>(this->getChildByTag(METEOR_PROG));
	if (meteor_prog->getPercentage() <= 0) {
		meteor_prog->setVisible(false);
		meteor_prog->setPercentage(100);
		unschedule(schedule_selector(GameUI::updateMeteor));
		_eventDispatcher->resumeEventListenersForTarget(meteor_prog);
		return;
	}
	meteor_prog->setPercentage(meteor_prog->getPercentage() - 1.0f);
}
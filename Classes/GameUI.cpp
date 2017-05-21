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
	addSkill("power_portrait_fireball_0001.png", "power_portrait_fireball_0002.png");
	addSkill("power_portrait_reinforcement_0001.png", "power_portrait_reinforcement_0002.png");

	// select target screen
	select_target_ = EventListenerTouchOneByOne::create();
	select_target_->setSwallowTouches(true);
	select_target_->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		int k = 0;
		for (k = 0; k < skills.size(); ++k) {
			if (skills[k].on_click) {
				break;
			}
		}

		// resume background
		skills[k].background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(skills[k].normal_image));

		// open progress
		skills[k].on_click = false;
		skills[k].on_doing = true;
		skills[k].progress_timer->setVisible(true);
		_eventDispatcher->pauseEventListenersForTarget(skills[k].progress_timer);
		select_target_->setEnabled(false);
		return true;
	};

	select_target_->setEnabled(false);
	_eventDispatcher->addEventListenerWithFixedPriority(select_target_, 1);

	schedule(schedule_selector(GameUI::updateSkills));

	return true;
}

void GameUI::addSkill(const char *skill_image, const char *skill_active_image) {
	int skill_id = skills.size();
	// add skill backgournd
	auto skill_bg = Sprite::createWithSpriteFrameName(skill_image);
	skill_bg->setAnchorPoint(Vec2(0, 0));
	skill_bg->setPosition(skill_id * skill_bg->getContentSize().width + 10.0f, 10.0f);
	this->addChild(skill_bg, 0);

	// the skill progress
	auto skill_progress = ProgressTimer::create(Sprite::createWithSpriteFrameName("power_loading.png"));
	skill_progress->setAnchorPoint(Point(0, 0));
	skill_progress->setReverseDirection(true);
	skill_progress->setPosition(skill_bg->getPosition());
	skill_progress->setPercentage(100);
	skill_progress->setVisible(false);
	this->addChild(skill_progress, 1);

	// add skill listener
	auto skill_listener = EventListenerTouchOneByOne::create();
	// UI swallow event
	skill_listener->setSwallowTouches(true);

	skill_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (skill_progress->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			return true;
		}
		return false;
	};

	skill_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		resetSkillsClick();
		if (!skills[skill_id].on_click) {
			skills[skill_id].on_click = true;
			skill_bg->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(skill_active_image));
			select_target_->setEnabled(true);
		} else {
			skills[skill_id].on_click = false;
			skill_bg->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(skill_image));
			select_target_->setEnabled(false);
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(skill_listener, skill_progress);
	// ready for next
	skills.push_back({ false, false, skill_progress, skill_bg, skill_image, skill_active_image });
}

void GameUI::updateSkills(float dt) {
	for (int i = 0; i < skills.size(); ++i) {
		if (skills[i].on_doing) {
			if (skills[i].progress_timer->getPercentage() <= 0) {
				skills[i].progress_timer->setVisible(false);
				skills[i].progress_timer->setPercentage(100);
				skills[i].on_doing = false;
				_eventDispatcher->resumeEventListenersForTarget(skills[i].progress_timer);
			}
			skills[i].progress_timer->setPercentage(skills[i].progress_timer->getPercentage() - 1.0f);
		}
	}
}

void GameUI::resetSkillsClick() {
	for (int i = 0; i < skills.size(); ++i) {
		skills[i].on_click = false;
		skills[i].background->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(skills[i].normal_image));
	}
}

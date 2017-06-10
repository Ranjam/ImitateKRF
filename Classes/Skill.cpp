#include "Skill.h"
#include "GameUI.h"


Skill::Skill() {
}


Skill::~Skill() {
}

bool Skill::init(std::string normal, std::string active) {

	if (!Sprite::init()) {
		return false;
	}

	this->is_clicked_ = false;
	this->is_ready_ = true;
	this->normal_image_ = SpriteFrameCache::getInstance()->getSpriteFrameByName(normal);
	this->active_image_ = SpriteFrameCache::getInstance()->getSpriteFrameByName(active);

	// add skill backgournd
	image_ = Sprite::createWithSpriteFrame(normal_image_);
	image_->setAnchorPoint(Vec2(0, 0));
	this->addChild(image_, 0);

	// the skill progress
	progress_timer_ = ProgressTimer::create(Sprite::createWithSpriteFrameName("power_loading.png"));
	progress_timer_->setAnchorPoint(Point(0, 0));
	progress_timer_->setReverseDirection(true);
	progress_timer_->setPosition(image_->getPosition());
	progress_timer_->setPercentage(100);
	progress_timer_->setVisible(false);
	this->addChild(progress_timer_, 1);

	// add skill listener
	auto skill_listener = EventListenerTouchOneByOne::create();
	// UI swallow event
	skill_listener->setSwallowTouches(true);

	skill_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (image_->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			return true;
		}
		return false;
	};

	skill_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		// if this is in CD state, swallow the event but not response
		if (!is_ready_) {
			return;
		}
		if (!is_clicked_) {
			static_cast<GameUI *>(this->getParent())->resetClickedSkills();
			this->onClick();
		} else {
			this->undoClick();
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(skill_listener, image_);

	// select target layer
	select_target_ = EventListenerTouchOneByOne::create();
	select_target_->setSwallowTouches(true);

	select_target_->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		return true;
	};
	select_target_->onTouchEnded = [=](Touch *touch, Event *event) {
		this->undoClick();
		this->coolDown(3);
		this->execute(touch, event);
	};
	_eventDispatcher->addEventListenerWithFixedPriority(select_target_, 1);
	select_target_->setEnabled(false);

	return true;
}

void Skill::onClick() {
	this->is_clicked_ = true;
	image_->setSpriteFrame(active_image_);
	this->select_target_->setEnabled(true);
}

void Skill::undoClick() {
	this->is_clicked_ = false;
	image_->setSpriteFrame(normal_image_);
	this->select_target_->setEnabled(false);
}

void Skill::coolDown(float time) {
	this->progress_timer_->setVisible(true);
	this->progress_timer_->setPercentage(100);
	this->is_ready_ = false;
	schedule(schedule_selector(Skill::processCoolDown), time / 100);
}

void Skill::processCoolDown(float dt) {
	if (progress_timer_->getPercentage() > 0) {
		progress_timer_->setPercentage(progress_timer_->getPercentage() - 1);
	} else {
		this->is_ready_ = true;
		this->unschedule(schedule_selector(Skill::processCoolDown));
	}
}

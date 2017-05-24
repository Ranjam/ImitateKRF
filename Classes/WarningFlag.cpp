#include "WarningFlag.h"
#include "Resources.h"

WarningFlag::WarningFlag() {
}

WarningFlag::~WarningFlag() {
}

bool WarningFlag::init() {
	if (!Sprite::init()) {
		return false;
	}

	// progressTimer_
	progressTimer_ = ProgressTimer::create(Sprite::createWithSpriteFrameName("waveFlag_0003.png"));
	progressTimer_->setType(ProgressTimer::Type::RADIAL);
	this->addChild(progressTimer_, 1);

	// flag bg
	auto flag_bg = Sprite::createWithSpriteFrameName("waveFlag_0001.png");
	flag_bg->setPosition(progressTimer_->getContentSize().width / 2, progressTimer_->getContentSize().height / 2);
	progressTimer_->addChild(flag_bg);

	// selected image
	auto selected = Sprite::createWithSpriteFrameName("waveFlag_selected.png");
	selected->setPosition(progressTimer_->getContentSize().width / 2, progressTimer_->getContentSize().height / 2);
	progressTimer_->addChild(selected);
	selected->setVisible(false);

	this->setScale(0.8f);
	this->setVisible(false);
	auto respiration = RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.6f, 0.6f), ScaleTo::create(0.6f, 0.8f, 0.8f), NULL));
	this->runAction(respiration);

	// on clicked
	auto select_listener = EventListenerTouchOneByOne::create();
	select_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (flag_bg->getBoundingBox().containsPoint(flag_bg->convertTouchToNodeSpace(touch))) {
			return true;
		}
		selected->setVisible(false);
		is_selected_ = false;
		return false;
	};

	select_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		if (!is_selected_) {
			is_selected_ = true;
			selected->setVisible(true);
		} else {
			this->stop();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(select_listener, flag_bg);

	return true;
}

void WarningFlag::setSpeed(float speed) {
	this->speed_ = speed;
}

float WarningFlag::getPercentage() const {
	return this->progressTimer_->getPercentage();
}

void WarningFlag::start() {
	this->setVisible(true);
	progressTimer_->setPercentage(0.0f);
	this->is_over_ = false;
	schedule(schedule_selector(WarningFlag::updateProgress), 0.1f / speed_);
}

void WarningFlag::stop() {
	progressTimer_->setPercentage(0);
	this->setVisible(false);
	this->is_over_ = true;
	this->stopAllActions();
	unschedule(schedule_selector(WarningFlag::updateProgress));
}

void WarningFlag::updateProgress(float dt) {
	progressTimer_->setPercentage(progressTimer_->getPercentage() + 0.1f);
	if (progressTimer_->getPercentage() >= 100) {
		this->stop();
	}
}

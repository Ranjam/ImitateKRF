#include "WarningFlag.h"

WarningFlag::WarningFlag() {
}

WarningFlag::~WarningFlag() {
}

bool WarningFlag::init() {
	if (!Sprite::init()) {
		return false;
	}
	// load file
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ingame_gui-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common_spritesheet_32-hd.plist");

	// progressTimer_
	progressTimer_ = ProgressTimer::create(Sprite::createWithSpriteFrameName("waveFlag_0003.png"));
	progressTimer_->setType(ProgressTimer::Type::RADIAL);
	this->addChild(progressTimer_, 1);

	// flag
	auto flag = Sprite::createWithSpriteFrameName("waveFlag_0001.png");
	flag->setPosition(progressTimer_->getContentSize().width / 2, progressTimer_->getContentSize().height / 2);
	progressTimer_->addChild(flag);

	// on click
	auto selected = Sprite::createWithSpriteFrameName("waveFlag_selected.png");
	selected->setPosition(progressTimer_->getContentSize().width / 2, progressTimer_->getContentSize().height / 2);
	progressTimer_->addChild(selected);
	selected->setVisible(false);

	this->setScale(0.8f);
	this->setVisible(false);
	auto respiration = RepeatForever::create(Sequence::create(ScaleTo::create(0.5f, 0.6f, 0.6f), ScaleTo::create(0.6f, 0.8f, 0.8f), NULL));
	this->runAction(respiration);

	return true;
}

void WarningFlag::setSpeed(float speed) {
	this->speed_ = speed;
}

void WarningFlag::restart() {
	this->setVisible(true);
	progressTimer_->setPercentage(0.0f);
	schedule(schedule_selector(WarningFlag::updateProgress), 0.1f / speed_);
}

void WarningFlag::stop() {
	progressTimer_->setPercentage(0);
	this->setVisible(false);
	this->stopAllActions();
	unschedule(schedule_selector(WarningFlag::updateProgress));
}

void WarningFlag::updateProgress(float dt) {
	progressTimer_->setPercentage(progressTimer_->getPercentage() + 0.1f);
	if (progressTimer_->getPercentage() >= 100) {
		this->stop();
	}
}

#include "Creature.h"



Creature::Creature() {
}


Creature::~Creature() {
}

bool Creature::init(int hp, int max_hp, float speed, float scope, bool is_removed, SpriteFrame* image, HP_Type hp_type) {
	if (!Sprite::init()) {
		return false;
	}

	this->hp_ = hp;
	this->max_hp_ = max_hp;
	this->speed_ = speed;
	this->scope_ = scope;
	this->is_removed_ = is_removed;
	this->target_ = nullptr;

	this->image_ = Sprite::createWithSpriteFrame(image);
	image_->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(image_);

	switch (hp_type) {
		case SMALL: 
			hp_bg_ = Sprite::createWithSpriteFrameName("lifebar_bg_small.png");
			hp_bg_->setPosition(0.0f, 40.0f);
			this->addChild(hp_bg_, 0);

			hp_prog_ = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_small.png"));
			hp_prog_->setType(ProgressTimer::Type::BAR);
			hp_prog_->setMidpoint(Vec2(0.0f, 0.5f));
			hp_prog_->setScaleY(1.5f);
			hp_prog_->setPercentage(100.0f);
			hp_prog_->setPosition(0.0f, 40.0f);
			this->addChild(hp_prog_, 1);
			break;
		case MIDDLE: break;
		case BIG: break;
	}

	return true;
}

void Creature::getDamage(float damage) {
	this->hp_ -= damage;
	this->hp_prog_->setPercentage(static_cast<float>(this->hp_) / this->max_hp_ * 100);
	if (this->hp_ <= 0) {
		this->unscheduleAllCallbacks();
		this->stopAllActions();
		this->is_removed_ = true;
		if (this->target_ != nullptr) {
			this->releaseTarget();
		}
		this->dying();
	}
}

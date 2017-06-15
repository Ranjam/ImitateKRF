#include "DesertThug.h"
#include "Common/SoundManager.h"
#include "Common/Resources.h"

DesertThug::DesertThug() {
}

DesertThug::~DesertThug() {
}

bool DesertThug::init(int type, const std::vector<Vec2> &path) {
	if (!Monster::init(100, // hp
					   100, // max hp
					   18.0f, // speed
					   100, // scope
					   false, // is removed
					   SpriteFrameCache::getInstance()->getSpriteFrameByName("desertThug_0067.png"),
					   HP_Type::SMALL,
					   type,
					   path
					   )) {
		return false;
	}

	return true;
}

void DesertThug::update(float dt) {
	// nothing to do
}

void DesertThug::setState(MonsterState state) {
	this->state_ = state;
	this->image_->stopActionByTag(0);
	Action *animationAct;
	switch (state) {

	case WALK_LEFT:
		this->image_->setFlippedX(true);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_forward")));
		break;
	case WALK_RIGHT:
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_forward")));
		break;
	case WALK_UP:
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_up")));
		break;
	case WALK_DOWN:
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_down")));
		break;
	case ATTACK_LEFT:
		this->image_->setFlippedX(true);
		attack(0.16f);
		return;
	case ATTACK_RIGHT:
		this->image_->setFlippedX(false);
		attack(0.16f);
		return;
	case STOP:
		this->stopAllActions();
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_stand")));
		break;
	}
	animationAct->setTag(0);
	image_->runAction(animationAct);
}

void DesertThug::attack(float dt) {
	if (!target_->getIsRemoved()) {
		this->image_->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_attack")),
												 CallFunc::create([=]() {
			target_->getDamage(30);
			if (!target_->getIsRemoved()) {
				scheduleOnce(schedule_selector(DesertThug::attack), 0.3f);
			} else {
				this->releaseTarget();
				this->keepGoing();
			}
		}),
												 NULL));
	} else {
		this->releaseTarget();
		keepGoing();
	}
}

void DesertThug::dying() {
	int rand = RandomHelper::random_int(1, 4);
	SoundManager::getInstance()->playEffect(StringUtils::format(s_human_dead, rand).c_str());

	this->image_->stopAllActions();
	this->stopAllActions();
	this->hp_bg_->setVisible(false);
	this->image_->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_dead")),
											 DelayTime::create(0.5f),
											 CallFunc::create([=](){
		this->setVisible(false);
		this->removeFromParent();
	}), NULL));
}

#include "Soldier.h"



Soldier::Soldier() {
}


Soldier::~Soldier() {
}

bool Soldier::init(ReinforceType type) {
	switch (type) {
		case A: 
			this->name_ = "reinforce_A3";
			break;
		case B: 
			this->name_ = "reinforce_B3";
			break;
		case C: 
			this->name_ = "reinforce_C3";
			break;
	}
	if (!Human::init(0, 100, 100, 100.0f, SpriteFrameCache::getInstance()->getSpriteFrameByName(this->name_ + "_0001.png"))) {
		return false;
	}

	schedule(schedule_selector(Soldier::chase), 1.0f);

	return true;
}

void Soldier::chase(float dt) {

	checkMonster();

	if (target_monster_ != nullptr) {
		auto relative = target_monster_->getPosition() - this->getPosition();
		if (relative.x > 0) {
			this->image_->setFlippedX(false);
		} else {
			this->image_->setFlippedX(true);
		}

		this->image_->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(this->name_ + "_move"))));

		Vec2 pos;
		if (target_monster_->getState() == Monster::MonsterState::WALK_LEFT) {
			pos = Vec2(relative.x - 30, relative.y);
		} else {
			pos = Vec2(relative.x + 30, relative.y);
		}

		this->runAction(Sequence::create(MoveBy::create(relative.length() / 50.0f, pos),
										 CallFunc::create([=]() mutable 
		{
			relative = target_monster_->getPosition() - this->getPosition();
			if (relative.x > 0) {
				this->image_->setFlippedX(false);
			} else {
				this->image_->setFlippedX(true);
			}
			this->image_->stopAllActions();
			attack(dt);
		}),
										 NULL));

		unschedule(schedule_selector(Soldier::chase));
		target_monster_->setState(Monster::MonsterState::STOP);
	}
}

void Soldier::attack(float dt) {

	if (!target_monster_->getIsRemoved()) {
		this->image_->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation(this->name_ + "_attack")),
												 CallFunc::create([=]() {
			if (!target_monster_->getIsRemoved()) {
				target_monster_->getDamage(30);
				scheduleOnce(schedule_selector(Soldier::attack), 0.3f);
			} else {
				schedule(schedule_selector(Soldier::chase), 0.16f, -1, 0.1f);
			}
		}),
												 NULL));
	} else {
		schedule(schedule_selector(Soldier::chase), 0.16f, -1, 0.1f);
	}
}

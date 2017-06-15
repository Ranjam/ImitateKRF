#include "Soldier.h"
#include "Monsters/Monster.h"


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
	if (!Human::init(100, 100, 100.0f, 100.0f, false, SpriteFrameCache::getInstance()->getSpriteFrameByName(this->name_ + "_0001.png"), HP_Type::SMALL)) {
		return false;
	}

	schedule(schedule_selector(Soldier::chase), 1.0f);

	return true;
}

void Soldier::chase(float dt) {

	checkMonster();

	if (target_ != nullptr) {
		auto target_monster = static_cast<Monster *>(target_);
		auto relative = target_monster->getPosition() - this->getPosition();
		if (relative.x > 0) {
			this->image_->setFlippedX(false);
		} else {
			this->image_->setFlippedX(true);
		}

		this->image_->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(this->name_ + "_move"))));

		Vec2 pos;
		if (target_monster->getState() == Monster::MonsterState::WALK_LEFT) {
			pos = Vec2(relative.x - 30, relative.y);
		} else {
			pos = Vec2(relative.x + 30, relative.y);
		}

		this->runAction(Sequence::create(MoveBy::create(relative.length() / 50.0f, pos),
										 CallFunc::create([=]() mutable 
		{
			relative = target_monster->getPosition() - this->getPosition();
			if (relative.x > 0) {
				this->image_->setFlippedX(false);
			} else {
				this->image_->setFlippedX(true);
			}
			this->image_->stopAllActions();
			attack(dt);

			//target_monster->setTarget(this);
			// todo: how to let the monster know Im coming
			if (relative.x > 0) {
				target_monster->setState(Monster::MonsterState::ATTACK_LEFT);
			} else {
				target_monster->setState(Monster::MonsterState::ATTACK_RIGHT);
			}
		}),
										 NULL));

		unschedule(schedule_selector(Soldier::chase));
		target_monster->setState(Monster::MonsterState::STOP);
	}
}

void Soldier::attack(float dt) {

	if (!target_->getIsRemoved()) {
		this->image_->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation(this->name_ + "_attack")),
												 CallFunc::create([=]() {
			target_->getDamage(30);
			if (!target_->getIsRemoved()) {
				scheduleOnce(schedule_selector(Soldier::attack), 0.3f);
			} else {
				this->releaseTarget();
				schedule(schedule_selector(Soldier::chase), 0.16f, -1, 0.1f);
			}
		}),
												 NULL));
	} else {
		this->releaseTarget();
		schedule(schedule_selector(Soldier::chase), 0.16f, -1, 0.1f);
	}
}

#include "Soldier.h"



Soldier::Soldier() {
}


Soldier::~Soldier() {
}

bool Soldier::init() {
	if (!Human::init(0, 100, 100, 100.0f, SpriteFrameCache::getInstance()->getSpriteFrameByName("reinforce_A3_0001.png"))) {
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

		this->image_->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("reinforce_A3_move"))));

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
			schedule(schedule_selector(Soldier::attack), 1.0f, -1, 0.1f);
		}),
										 NULL));

		unschedule(schedule_selector(Soldier::chase));
		target_monster_->setState(Monster::MonsterState::STOP);
	}
}

void Soldier::attack(float dt) {

	if (!target_monster_->getIsRemoved()) {
		this->image_->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("reinforce_A3_attack")),
												 CallFunc::create([=]() {target_monster_->getDamage(30); }),
												 NULL));
	} else {
		unschedule(schedule_selector(Soldier::attack));
		schedule(schedule_selector(Soldier::chase));
	}
}

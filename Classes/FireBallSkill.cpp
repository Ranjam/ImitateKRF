#include "FireBallSkill.h"
#include "FireballBullet.h"
#include "FightScene.h"


FireBallSkill::FireBallSkill() {
}


FireBallSkill::~FireBallSkill() {
}

bool FireBallSkill::init() {
	if (!Skill::init("power_portrait_fireball_0001.png", "power_portrait_fireball_0002.png")) {
		return false;
	}

	return true;
}

void FireBallSkill::execute(Touch* touch, Event* event) {
	this->origin_pos_ = GameManager::getInstance()->getBattlefield()->convertTouchToNodeSpace(touch);
	schedule(schedule_selector(FireBallSkill::Instantiate), 0.3f, 4, 0.5f);
}

void FireBallSkill::Instantiate(float dt) {
	Vec2 pos = Vec2(origin_pos_.x + RandomHelper::random_real(-15.0f, 15.0f), origin_pos_.y + RandomHelper::random_real(-15.0f, 15.0f));
	auto fireball = FireballBullet::create();
	GameManager::getInstance()->getBattlefield()->addChild(fireball, 999);
	fireball->setPosition(pos);
	fireball->attack();
}

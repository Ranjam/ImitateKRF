#include "ReinforcementSkill.h"
#include "Common/GameManager.h"
#include "Scenes/Battlefield.h"
#include "Heros/Soldier.h"


ReinforcementSkill::ReinforcementSkill() {
}


ReinforcementSkill::~ReinforcementSkill() {
}

bool ReinforcementSkill::init() {
	if (!Skill::init("power_portrait_reinforcement_0001.png", "power_portrait_reinforcement_0002.png")) {
		return false;
	}

	return true;
}

void ReinforcementSkill::execute(Touch* touch, Event* event) {
	Vec2 pos = GameManager::getInstance()->getBattlefield()->convertTouchToNodeSpace(touch);
	auto soldier1 = Soldier::create(Soldier::ReinforceType::A);
	soldier1->setPosition(Vec2(pos.x + 20, pos.y + 20));
	GameManager::getInstance()->getBattlefield()->addChild(soldier1, 3);

	auto soldier2 = Soldier::create(Soldier::ReinforceType::B);
	soldier2->setPosition(Vec2(pos.x - 20, pos.y + 20));
	GameManager::getInstance()->getBattlefield()->addChild(soldier2, 3);

	auto soldier3 = Soldier::create(Soldier::ReinforceType::C);
	soldier3->setPosition(Vec2(pos.x, pos.y - 10));
	GameManager::getInstance()->getBattlefield()->addChild(soldier3, 3);

}

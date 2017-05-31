#include "BaseTower.h"
#include "GameManager.h"


BaseTower::BaseTower() {
}


BaseTower::~BaseTower() {
}

bool BaseTower::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}

void BaseTower::checkNearestMonster() {
	// 全局Vector变量，用来存储当前关卡的敌人  
	auto monsters = GameManager::getInstance()->Monsters();

	nearest_monster_ = nullptr;
	for (int i = 0; i < monsters.size(); i++) {
		auto monster = monsters.at(i);
		double distance = this->getParent()->getPosition().getDistance(monster->getPosition());

		// 当在塔的范围内，且怪物可以被攻击（某些地下怪物只有钻出地面可以被攻击）
		if (distance < this->scope_) {   
			this->scope_ = distance;// 设置最小距离，找到最近的怪物  
			nearest_monster_ = monster;
		}
	}
}

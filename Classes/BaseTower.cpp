#include "BaseTower.h"
#include "GameManager.h"


BaseTower::BaseTower(
	TowerType type,
	std::string name,
	int level,
	float scope,
	float next_scope,
	float rate,
	float power,
	int upgrade_price,
	int selling_price,
	Monster* nearest_monster): 
	  type_(type)
	, level_(level)
	, scope_(scope)
	, next_scope_(next_scope)
	, rate_(rate)
	, power_(power)
	, upgrade_price_(upgrade_price)
	, selling_price(selling_price)
	, nearest_monster_(nearest_monster) {
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


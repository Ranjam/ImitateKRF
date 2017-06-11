#include "BaseTower.h"
#include "Common/GameManager.h"
#include "Scenes/MonsterLayer.h"


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

	double distance = 0.0f;

	if (this->nearest_monster_ != nullptr) {
		// if monster is dead or monster beyond attack scope, release the handle
		distance = this->getParent()->getPosition().getDistance(this->nearest_monster_->getPosition());
		if (this->nearest_monster_->getIsRemoved() || distance > this->scope_) {
			this->nearest_monster_->release();
			this->nearest_monster_ = nullptr;
		}
	}
	if (this->nearest_monster_ == nullptr) {
		for (auto monster : GameManager::getInstance()->getMonsterLayer()->getMonsters()) {
			distance = this->getParent()->getPosition().getDistance(monster->getPosition());
			// if monster can be attack, handle it
			if (distance < this->scope_) {
				this->nearest_monster_ = monster;
				this->nearest_monster_->retain();
				break;
			}
		}
	}
}


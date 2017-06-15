#include "Human.h"
#include "Common/GameManager.h"
#include "Scenes/MonsterLayer.h"


Human::Human() {
}


Human::~Human() {
}

bool Human::init(int hp, int max_hp, float speed, float scope, bool is_removed, SpriteFrame *sprite_frame, Creature::HP_Type hp_type) {
	if (!Creature::init(hp, max_hp, speed, scope, is_removed, sprite_frame, hp_type)) {
		return false;
	}

	return true;
}

void Human::checkMonster() {
	double distance;

	if (this->target_ != nullptr) {
		// if monster is dead or monster beyond attack scope, release the handle
		if (this->target_->getIsRemoved()) {
			this->releaseTarget();
		}
	}
	if (this->target_ == nullptr) {
		for (auto monster : GameManager::getInstance()->getMonsterLayer()->getMonsters()) {
			distance = this->getPosition().getDistance(monster->getPosition());
			// if monster can be attack, handle it
			if (distance < this->scope_ && monster->getTarget() == nullptr) {
				this->setTarget(monster);
				monster->setTarget(this);
				break;
			}
		}
	}
}

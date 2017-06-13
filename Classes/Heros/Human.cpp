#include "Human.h"
#include "Common/GameManager.h"
#include "Scenes/MonsterLayer.h"


Human::Human() {
}


Human::~Human() {
}

bool Human::init(int type, int hp, int max_hp, float scope, SpriteFrame *sprite_frame) {
	if (!Sprite::init()) {
		return false;
	}

	this->type_ = type;
	this->hp_ = hp;
	this->max_hp_ = max_hp;
	this->scope_ = scope;
	this->image_ = Sprite::createWithSpriteFrame(sprite_frame);
	image_->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(image_);
	//image_->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("reinforce"))));

	return true;
}

void Human::checkMonster() {
	double distance = 0.0f;

	if (this->target_monster_ != nullptr) {
		// if monster is dead or monster beyond attack scope, release the handle
		if (this->target_monster_->getIsRemoved()) {
			this->target_monster_->release();
			this->target_monster_ = nullptr;
		}
	}
	if (this->target_monster_ == nullptr) {
		for (auto monster : GameManager::getInstance()->getMonsterLayer()->getMonsters()) {
			distance = this->getPosition().getDistance(monster->getPosition());
			// if monster can be attack, handle it
			if (distance < this->scope_) {
				this->target_monster_ = monster;
				this->target_monster_->retain();
				break;
			}
		}
	}
}

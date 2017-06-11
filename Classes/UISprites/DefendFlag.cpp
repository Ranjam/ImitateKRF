#include "DefendFlag.h"
#include "Common/GameManager.h"
#include "Scenes/Battlefield.h"


DefendFlag::DefendFlag() {
}


DefendFlag::~DefendFlag() {
}

bool DefendFlag::init() {
	if (!Sprite::init()) {
		return false;
	}

	this->initWithSpriteFrameName("defendFlag_0069.png");

	auto sprite = Sprite::createWithSpriteFrameName("defendFlag_0060.png");
	sprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(sprite);

	sprite->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.2f), FadeIn::create(1.2f), NULL)));
	
	scheduleUpdate();

	return true;
}

void DefendFlag::update(float dt) {
	auto &monsters = GameManager::getInstance()->getMonsterLayer()->getMonsters();
	for (auto iter = monsters.begin(); iter != monsters.end(); ) {
		auto monster_pos = this->getParent()->convertToNodeSpace((*iter)->getParent()->convertToWorldSpace((*iter)->getPosition()));
		if (this->getBoundingBox().containsPoint(monster_pos)) {
			GameManager::getInstance()->setLife(GameManager::getInstance()->getLife() - 1);
			(*iter)->removeFromParent();
			(*iter)->setIsRemoved(true);
			iter = monsters.erase(iter);
		} else {
			++iter;
		}
	}
}

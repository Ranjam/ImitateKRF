#include "Battlefield.h"
#include "MonsterLayer.h"
#include "Monsters/DesertThug.h"
#include "Common/GameManager.h"
#include "Common/SoundManager.h"
#include "Common/Resources.h"


MonsterLayer::MonsterLayer() {
}


MonsterLayer::~MonsterLayer() {
}

bool MonsterLayer::init() {

	if (!Layer::init()) {
		return false;
	}

	scheduleUpdate();

	GameManager::getInstance()->setMonsterLayer(this);

	return true;
}

void MonsterLayer::nextWave() {
	if (wave_over_) {
		SoundManager::getInstance()->playEffect(s_effect_wave_incoming);
		schedule(schedule_selector(MonsterLayer::monsterIncoming), 1.0f);
		wave_over_ = false;
	}
}

void MonsterLayer::cleanUpMonster() {
	for (auto iter = monsters_.begin(); iter != monsters_.end(); ) {
		if ((*iter)->getIsRemoved()) {
			iter = monsters_.erase(iter);
		} else {
			++iter;
		}
	}
}

void MonsterLayer::update(float dt) {
	cleanUpMonster();
}

Monster* MonsterLayer::generateMonster(int type, int path) {
	switch (type) {
		case 0: {
			Monster *monster = DesertThug::create(type, this->paths_.at(path));
			return monster;
		}
		default: {
			Monster *monster = DesertThug::create(type, this->paths_.at(path));
			return monster;
		}
	}
}

void MonsterLayer::monsterIncoming(float dt) {
	int current_wave = GameManager::getInstance()->getCurrentWave() - 1;
	if (current_monster_ < monster_info_.at(current_wave).size()) {
		auto monster_info = monster_info_.at(current_wave).at(current_monster_);
		auto monster = generateMonster(monster_info.type, monster_info.path);

		// different monsters have different z-order
		this->addChild(monster, static_cast<int>(1000 - monster->getPosition().y));

		monster->keepGoing();
		monsters_.pushBack(monster);
		++current_monster_;
	} else {
		unschedule(schedule_selector(MonsterLayer::monsterIncoming));
		current_monster_ = 0;
		wave_over_ = true;
		static_cast<Battlefield *>(this->getParent())->waveOver();
	}
}

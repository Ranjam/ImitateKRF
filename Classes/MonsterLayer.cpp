#include "MonsterLayer.h"
#include "DesertThug.h"
#include "GameManager.h"


MonsterLayer::MonsterLayer() {
}


MonsterLayer::~MonsterLayer() {
}

bool MonsterLayer::init() {

	if (!Layer::init()) {
		return false;
	}

	return true;
}

void MonsterLayer::nextWave() {
	if (wave_over_ && GameManager::getInstance()->getCurrentWave() < GameManager::getInstance()->getWaveCount()) {
		schedule(schedule_selector(MonsterLayer::monsterIncoming), 3.0f);
		wave_over_ = false;
	}
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
	int current_wave = GameManager::getInstance()->getCurrentWave();
	if (current_monster_ < monster_info_.at(current_wave).size()) {
		auto monster_info = monster_info_.at(current_wave).at(current_monster_);
		auto monster = generateMonster(monster_info.type, monster_info.path);

		// different monsters have different z-order
		this->addChild(monster, static_cast<int>(1000 - monster->getPosition().y));

		monster->keepGoing();
		GameManager::getInstance()->getMonsters().pushBack(monster);
		++current_monster_;
	} else {
		unschedule(schedule_selector(MonsterLayer::monsterIncoming));
		GameManager::getInstance()->setCurrentWave(current_wave + 1);
		current_monster_ = 0;
		wave_over_ = true;
	}
}

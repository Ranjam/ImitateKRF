#include "MonsterLayer.h"
#include "DesertThug.h"
#include "Resources.h"
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
	if (wave_over_ && current_wave_ < monster_info_.size()) {
		schedule(schedule_selector(MonsterLayer::monsterIncoming), 1.0f);
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
	if (current_monster_ < monster_info_.at(current_wave_).size()) {
		auto monster_info = monster_info_.at(current_wave_).at(current_monster_);
		auto monster = generateMonster(monster_info.type, monster_info.path);
		this->addChild(monster);
		monster->keepGoing();
		GameManager::getInstance()->getMonsters().pushBack(monster);
		++current_monster_;
	} else {
		unschedule(schedule_selector(MonsterLayer::monsterIncoming));
		++current_wave_;
		current_monster_ = 0;
		wave_over_ = true;
	}
}

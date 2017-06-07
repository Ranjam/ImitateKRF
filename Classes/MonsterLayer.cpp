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

	loadLevelData();

	return true;
}

void MonsterLayer::nextWave() {
	if (wave_over_ && current_wave_ < monster_info_.size()) {
		schedule(schedule_selector(MonsterLayer::monsterIncoming), 1.0f);
		wave_over_ = false;
	}
}

void MonsterLayer::loadLevelData() {
	// all level data
	auto data_map = FileUtils::getInstance()->getValueMapFromFile("test.plist");

	// level base data
	auto level_data = data_map.at("level_data").asValueMap();
	GameManager::getInstance()->setGold(level_data.at("gold").asInt());
	GameManager::getInstance()->setLife(level_data.at("life").asInt());
	GameManager::getInstance()->setWaveCount(level_data.at("wave_count").asInt());

	// level monsters
	auto level_monsters = data_map.at("monsters").asValueVector();
	for (int i = 0; i < level_monsters.size(); ++i) {
		// for every wave
		auto wave_monsters = level_monsters.at(i).asValueVector();
		std::vector<MonsterInfo> monster_infos;
		for (int j = 0; j < wave_monsters.size(); ++j) {
			monster_infos.push_back({ wave_monsters.at(j).asValueMap().at("type").asInt(),
									  wave_monsters.at(j).asValueMap().at("path").asInt() });
		}
		this->monster_info_.push_back(monster_infos);
	}

	// level paths
	auto level_paths = data_map.at("paths").asValueVector();
	for (int i = 0; i < level_paths.size(); ++i) {
		// for every path
		auto paths = level_paths.at(i).asValueVector();
		std::vector<Vec2> path;
		for (int j = 0; j < paths.size(); ++j) {
			auto point = paths.at(j).asValueMap();
			path.push_back(Vec2(point.at("x").asFloat(), point.at("y").asFloat()));
		}
		this->paths_.push_back(path);
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

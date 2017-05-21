#include "FightScene.h"
#include "Resources.h"
#include "Common.h"

FightScene::FightScene() { }

FightScene::~FightScene() { }

bool FightScene::init() {
	if (!Layer::init()) {
		return false;
	}
	
	// load monster data
	loadMonsterData();

	// load paths data
	loadPathData();

	map_ = BaseMap::create(1);
	this->addChild(map_, ZORDER::MAP);

	ui_ = GameUI::create();
	this->addChild(ui_, ZORDER::GAME_UI);

	return true;
}

void FightScene::loadMonsterData() {
	auto data_map = FileUtils::getInstance()->getValueMapFromFile(s_level_01_plist);

	// 初始数据
	auto map_base_data = data_map.at("data").asValueVector().at(0).asValueMap();
	start_gold_ = map_base_data.at("gold").asInt();
	start_life_ = map_base_data.at("life").asInt();
	max_wave_ = map_base_data.at("wave").asInt();

	// 怪物数据
	// 本关所有怪物
	auto all_monsters = data_map.at("monsters").asValueVector();
	for (int i = 0; i < all_monsters.size(); ++i) {
		std::vector<Vector<Monster *>> wave_monsters;
		// 本波所有怪物
		auto all_wave_monsters = all_monsters.at(i).asValueVector();
		for (int j = 0; j < all_wave_monsters.size(); ++j) {
			Vector<Monster *> frame_monsters;
			auto all_frame_monsters = all_wave_monsters.at(j).asValueVector();
			for (int k = 0; k < all_frame_monsters.size(); ++k) {
				// 本帧所有怪物
				auto monster = all_frame_monsters.at(k).asValueMap();
				auto type = monster.at("type").asInt();
				auto path = monster.at("path").asInt();
				auto road = monster.at("road").asInt();
				frame_monsters.pushBack(Monster::create(type, road, path));
			}
			wave_monsters.push_back(frame_monsters);
			frame_monsters.clear();
		}
		monsters_.push_back(wave_monsters);
		wave_monsters.clear();
	}
}

void FightScene::loadPathData() {
	auto path_map = FileUtils::getInstance()->getValueMapFromFile(s_level_01_path_plist);

	auto path_array = path_map.at("paths").asValueVector();
	for (int i = 0; i < path_array.size(); ++i) {
		std::vector<std::vector<Vec2>> all_paths;
		auto paths = path_array.at(i).asValueVector();
		for (int j = 0; j < paths.size(); ++j) {
			std::vector<Vec2> single_path;
			auto path = paths.at(j).asValueVector();
			for (int k = 0; k < path.size(); ++k) {
				auto point = path.at(k).asValueMap();
				single_path.push_back(Vec2(point.at("x").asFloat(), point.at("y").asFloat()));
			}
			all_paths.push_back(single_path);
			single_path.clear();
		}
		monster_paths_.push_back(all_paths);
		all_paths.clear();
	}
}

void FightScene::updateWaves(float dt) {
	
	for (int i = 0; i < warning_flags_.size(); i++) {
		if (warning_flags_.at(i)->getPercentage() == 100.0f) {
			if (current_wave_ < max_wave_) {
				// SoundManager::playIncomingWave();
				current_wave_++;
				for (int j = 0; j < warning_flags_.size(); i++) {
					warning_flags_.at(i)->stop();
				}
				break;
			}
		}
	}
}

void FightScene::addMonsters(float dt) {

	//static float timing = 0.0f;
	//if (timing >= 15.0f) {
	//	for (int i = 0; i < waveVector.at(wave).at(time).size(); i++) {
	//		auto monsterData = waveVector.at(wave).at(time).at(i);
	//		switch (monsterData->getType()) {
	//		case(0):
	//		{
	//			auto thug = Thug::createMonster(monster_paths_.at(monsterData->getRoad()).at(monsterData->getPath()));
	//			this->addChild(thug);
	//			GameManager::getInstance()->monsterVector.pushBack(thug);
	//		}
	//		break;
	//		}
	//	}
	//	timing = 0.0f;
	//} else {
	//	timing++;
	//	if (current_wave_ != max_wave_ - 1) {
	//		// SoundManager::playNextWaveReady();
	//		scheduleOnce(schedule_selector(FightScene::showWaveProgressBars), 15.0f);
	//	}
	//}
}

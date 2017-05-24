#include "MonsterLayer.h"
#include "DesertThug.h"
#include "Resources.h"


MonsterLayer::MonsterLayer() {
}


MonsterLayer::~MonsterLayer() {
}

bool MonsterLayer::init() {

	if (!Layer::init()) {
		return false;
	}

	// load paths data
	loadPathData();

	// load monsters data
	loadMonstersData();

	nextWave(0);

	//Monster *monster = DesertThug::create(0, 0, monster_paths_.at(0).at(0));
	//monster->setPosition(monster_paths_.at(0).at(0).at(0));
	//this->addChild(monster);
	//monster->keepGoing();

	//Monster *monster2 = DesertThug::create(0, 0, monster_paths_.at(0).at(1));
	//monster2->setPosition(monster_paths_.at(0).at(1).at(0));
	//this->addChild(monster2);
	//monster2->keepGoing();

	//Monster *monster3 = DesertThug::create(0, 0, monster_paths_.at(0).at(2));
	//monster3->setPosition(monster_paths_.at(0).at(2).at(0));
	//this->addChild(monster3);
	//monster3->keepGoing();

	//Monster *monster4 = DesertThug::create(0, 0, monster_paths_.at(1).at(2));
	//monster4->setPosition(monster_paths_.at(1).at(2).at(0));
	//this->addChild(monster4);
	//monster4->keepGoing();

	return true;
}

// load monster's path
void MonsterLayer::loadPathData() {
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

// load monster's data
void MonsterLayer::loadMonstersData() {
	// 怪物数据
	auto data_map = FileUtils::getInstance()->getValueMapFromFile(s_level_01_plist);

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
				frame_monsters.pushBack(generateMonster(type, path, road));
			}
			wave_monsters.push_back(frame_monsters);
			frame_monsters.clear();
		}
		this->monsters_.push_back(wave_monsters);
		wave_monsters.clear();
	}
}

void MonsterLayer::nextWave(float dt) {
	// every wave
	static int current_frame = 0;
	if (current_frame < monsters_[current_wave_].size()) {
		// every frame per 5 seconds
		schedule(schedule_selector(MonsterLayer::nextWave), 3.0f);
		for (int i = 0; i < monsters_[current_wave_][current_frame].size(); ++i) {
			this->addChild(monsters_[current_wave_][current_frame].at(i));
			monsters_[current_wave_][current_frame].at(i)->keepGoing();
		}
		++current_frame;
	} else {
		current_frame = 0;
		current_wave_++;
		unschedule(schedule_selector(MonsterLayer::nextWave));
	}
}

Monster* MonsterLayer::generateMonster(int type, int path, int road) {
	switch (type) {
	case 0:
	{
		Monster *monster = DesertThug::create(0, 0, monster_paths_.at(road).at(path));
		//monster->retain();
		return monster;
	}
	default:
	{
		Monster *monster = DesertThug::create(0, 0, monster_paths_.at(road > 1 ? 1 : road).at(road > 2 ? 2 : road));
		//monster->retain();
		return monster;
	}
	}
}

#include "BaseMap.h"

BaseMap::BaseMap() {
}


BaseMap::~BaseMap() {
}

bool BaseMap::init() {
	if (!Layer::init()) {
		return false;
	}
	
	//loadMonsterData();
	//loadPathData();
	return true;
}

void BaseMap::loadMonsterData() {
	auto data_map = FileUtils::getInstance()->getValueMapFromFile("level01.plist");

	// 初始数据
	auto map_base_data = data_map.at("data").asValueVector().at(0).asValueMap();
	start_gold_ = map_base_data.at("gold").asString();
	start_life_ = map_base_data.at("life").asString();
	start_wave_ = map_base_data.at("wave").asString();

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

void BaseMap::loadPathData() {
	auto path_map = FileUtils::getInstance()->getValueMapFromFile("level0_paths.plist");

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

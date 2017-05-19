#include "BaseMap.h"

BaseMap::BaseMap() {
}


BaseMap::~BaseMap() {
}

bool BaseMap::init() {
	if (!Layer::init()) {
		return false;
	}
	loadLevelData();
	return true;
}

void BaseMap::loadLevelData() {
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
		Vector<Vector<Monster *>> wave_monsters;
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
			wave_monsters.pushBack(frame_monsters);
			frame_monsters.clear();
		}
		monsters_.pushBack(wave_monsters);
		wave_monsters.clear();
	}
}

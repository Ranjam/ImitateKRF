#include "FightScene.h"
#include "Common.h"
#include "Resources.h"
#include "Monster.h"

FightScene::FightScene() { }

FightScene::~FightScene() { }

bool FightScene::init() {
	if (!Layer::init()) {
		return false;
	}

	// load monster data
	loadMonsterData();

	battle_field_ = Battlefield::create(1);
	this->addChild(battle_field_, ZORDER::BATTLEFIELD);

	ui_ = GameUI::create();
	this->addChild(ui_, ZORDER::GAME_UI);

	return true;
}

void FightScene::loadMonsterData() {
	auto data_map = FileUtils::getInstance()->getValueMapFromFile(s_level_01_plist);

	// ³õÊ¼Êı¾İ
	auto map_base_data = data_map.at("data").asValueVector().at(0).asValueMap();
	start_gold_ = map_base_data.at("gold").asInt();
	start_life_ = map_base_data.at("life").asInt();
	max_wave_ = map_base_data.at("wave").asInt();
}

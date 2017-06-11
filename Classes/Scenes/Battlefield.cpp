#include "Battlefield.h"
#include "Common/CommonMacro.h"
#include "Common/GameManager.h"
#include "UISprites/Stronghold.h"
#include "UISprites/DefendFlag.h"
#include "UISprites/WarningFlag.h"

Battlefield::Battlefield() {
}


Battlefield::~Battlefield() {
}

bool Battlefield::init(int level) {
	
	if (!Layer::init()) {
		return false;
	}

	// map
	map_ = BaseMap::create(level);
	map_->setAnchorPoint(Vec2(0, 0));
	map_->setPosition(0, 0);
	this->addChild(map_, Zorder::MAP);

	// monsters
	monster_layer_ = MonsterLayer::create();
	monster_layer_->setAnchorPoint(Vec2(0, 0));
	monster_layer_->setPosition(0, 0);
	this->addChild(monster_layer_, Zorder::MONSTER_LAYER);

	// load level data
	loadLevelData();

	// on moved
	auto touch_move_listener = EventListenerTouchOneByOne::create();
	touch_move_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		return true;
	};

	touch_move_listener->onTouchMoved = [=](Touch *touch, Event *event) {
		auto targetPostion = this->getPosition() + touch->getDelta();
		targetPostion.x = MIN(0, targetPostion.x);
		targetPostion.x = MAX(winSize.width - map_->getMapSize().width, targetPostion.x);
		targetPostion.y = MIN(0, targetPostion.y);
		targetPostion.y = MAX(winSize.height - map_->getMapSize().height, targetPostion.y);
		this->setPosition(targetPostion);
	};

#if 0
	// debug to decide point
	touch_move_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		auto point = this->monster_layer_->convertTouchToNodeSpace(touch);
		log("<dict>"
			"<key>x</key>"
			"<string>%g</string>"
			"<key>y</key>"
			"<string>%g</string>"
			"</dict>",
			point.x, point.y);
	};
#endif

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_move_listener, this);

	// add this to GameManager
	GameManager::getInstance()->setBattlefield(this);

	return true;
}

void Battlefield::nextWave() {
	for (int i = 0; i < warning_flags_info_.size(); ++i) {
		this->removeChildByTag(Tag::WARNING_FLAG + i);
	}
	if (GameManager::getInstance()->getCurrentWave() != GameManager::getInstance()->getWaveCount()) {
		GameManager::getInstance()->setCurrentWave(GameManager::getInstance()->getCurrentWave() + 1);
		monster_layer_->nextWave();
	}
}

void Battlefield::waveOver() {
	if (GameManager::getInstance()->getCurrentWave() != GameManager::getInstance()->getWaveCount()) {
		for (int i = 0; i < warning_flags_info_.size(); ++i) {
			auto warning_flag = WarningFlag::create();
			warning_flag->setPosition(warning_flags_info_.at(i));
			this->addChild(warning_flag, 1, Tag::WARNING_FLAG + i);
			warning_flag->start();
		}
	}
}

void Battlefield::loadLevelData() {
	// all level data
	auto data_map = FileUtils::getInstance()->getValueMapFromFile("level_01_info.plist");

	// level base data
	auto level_data = data_map.at("level_data").asValueMap();
	GameManager::getInstance()->setGold(level_data.at("gold").asInt());
	GameManager::getInstance()->setLife(level_data.at("life").asInt());
	GameManager::getInstance()->setWaveCount(level_data.at("wave_count").asInt());
	// set current wave
	GameManager::getInstance()->setCurrentWave(0);

	// defend flags
	auto level_defend_flags = data_map.at("defend_flag").asValueVector();
	for (auto value : level_defend_flags) {
		auto info = value.asValueMap();
		auto defend_flag = DefendFlag::create();
		defend_flag->setPosition(info.at("x").asFloat(), info.at("y").asFloat());
		this->addChild(defend_flag, 1);
	}

	// warning flags
	auto level_warning_flags = data_map.at("warning_flag").asValueVector();
	for (auto i = 0; i < level_warning_flags.size(); ++i) {
		auto info = level_warning_flags.at(i).asValueMap();
		Vec2 pos = Vec2(info.at("x").asFloat(), info.at("y").asFloat());
		this->warning_flags_info_.push_back(pos);
		auto warning_flag = WarningFlag::create();
		warning_flag->setPosition(pos);
		this->addChild(warning_flag, 1, Tag::WARNING_FLAG + i);
	}

	// stronghold
	auto level_stronghold = data_map.at("stronghold").asValueVector();
	for (size_t i = 0; i < level_stronghold.size(); ++i) {
		auto stronghold_info = level_stronghold.at(i).asValueMap();
		auto hold = Stronghold::create();
		hold->setPosition(stronghold_info.at("x").asFloat(), stronghold_info.at("y").asFloat());
		this->addChild(hold, 1);
	}

	// level monsters
	auto level_monsters = data_map.at("monsters").asValueVector();
	for (size_t i = 0; i < level_monsters.size(); ++i) {
		// for every wave
		auto wave_monsters = level_monsters.at(i).asValueVector();
		std::vector<MonsterLayer::MonsterInfo> monster_infos;
		for (size_t j = 0; j < wave_monsters.size(); ++j) {
			monster_infos.push_back({ wave_monsters.at(j).asValueMap().at("type").asInt(),
									wave_monsters.at(j).asValueMap().at("path").asInt() });
		}
		this->monster_layer_->getMonsterInfo().push_back(monster_infos);
	}

	// level paths
	auto level_paths = data_map.at("paths").asValueVector();
	for (size_t i = 0; i < level_paths.size(); ++i) {
		// for every path
		auto paths = level_paths.at(i).asValueVector();
		std::vector<Vec2> path;
		for (size_t j = 0; j < paths.size(); ++j) {
			auto point = paths.at(j).asValueMap();
			path.push_back(Vec2(point.at("x").asFloat(), point.at("y").asFloat()));
		}
		this->monster_layer_->getPaths().push_back(path);
	}
}

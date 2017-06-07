#include "Battlefield.h"
#include "Common.h"
#include "Stronghold.h"
#include "GameManager.h"

Battlefield::Battlefield() {
}


Battlefield::~Battlefield() {
}

bool Battlefield::init(int level) {
	
	if (!Layer::init()) {
		return false;
	}

	schedule(schedule_selector(Battlefield::updateWave), 1 / 60.0f);

	// map
	map_ = BaseMap::create(level);
	map_->setAnchorPoint(Vec2(0, 0));
	map_->setPosition(0, 0);
	this->addChild(map_, -1);

	// monsters
	monster_layer_ = MonsterLayer::create();
	monster_layer_->setAnchorPoint(Vec2(0, 0));
	monster_layer_->setPosition(0, 0);
	this->addChild(monster_layer_, 1);

	// warning flag
	auto flag = WarningFlag::create();
	flag->setPosition(1085, winSize.height / 2 + 172);
	flag->setSpeed(10);
	this->addChild(flag, 2);
	warning_flags_ = flag;

	// stronghold
	//auto hold = Stronghold::create();
	//hold->setPosition(winSize.width / 2 + 200, winSize.height / 2 + 180);
	//this->addChild(hold, 1);

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
		targetPostion.x = MAX(winSize.width - map_->getContentSize().width, targetPostion.x);
		targetPostion.y = MIN(0, targetPostion.y);
		targetPostion.y = MAX(winSize.height - map_->getContentSize().height, targetPostion.y);
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
	return true;
}

void Battlefield::updateWave(float dt) {
	if (monster_layer_->allOver()) {
		unschedule(schedule_selector(Battlefield::updateWave));
		return;
	}
	if (warning_flags_->isOver() && monster_layer_->waveIsOver()) {
		monster_layer_->nextWave();
		unschedule(schedule_selector(Battlefield::updateWave));
		schedule(schedule_selector(Battlefield::updateFlag), dt);
	}
}

void Battlefield::updateFlag(float dt) {
	if (monster_layer_->waveIsOver() && warning_flags_->isOver()) {
		warning_flags_->start();
		unschedule(schedule_selector(Battlefield::updateFlag));
		schedule(schedule_selector(Battlefield::updateWave));
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

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

	battle_field_ = Battlefield::create(1);
	this->addChild(battle_field_, ZORDER::BATTLEFIELD);

	ui_ = GameUI::create();
	this->addChild(ui_, ZORDER::GAME_UI);

	return true;
}

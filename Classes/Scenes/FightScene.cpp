#include "FightScene.h"
#include "Common/CommonMacro.h"
#include "Common/SoundManager.h"
#include "Common/Resources.h"

FightScene::FightScene() { }

FightScene::~FightScene() { }

bool FightScene::init(int level) {
	if (!Layer::init()) {
		return false;
	}

	battle_field_ = Battlefield::create(level);
	this->addChild(battle_field_, ZORDER::BATTLEFIELD);

	ui_ = GameUI::create();
	this->addChild(ui_, ZORDER::GAME_UI);

	SoundManager::getInstance()->stopMusic(true);
	SoundManager::getInstance()->playMusic(s_music_desert_battle);

	return true;
}

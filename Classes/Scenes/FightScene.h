#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "cocos2d.h"
#include "Battlefield.h"
#include "UI/GameUI.h"

USING_NS_CC;

class FightScene: public Layer {
public:
	FightScene();
	~FightScene();

	static Scene *createScene(int level) {
		auto scene = Scene::create();

		auto layer = FightScene::create(level);

		scene->addChild(layer);

		return scene;
	}

	static FightScene* create(int level) {
		FightScene* pRet = new(std::nothrow) FightScene();
		if (pRet && pRet->init(level)) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		return nullptr;
	};

	bool init(int level);

private:
	Battlefield *battle_field_;
	GameUI *ui_;
	int level_;

	enum ZORDER {
		BATTLEFIELD, GAME_UI
	};
};

#endif

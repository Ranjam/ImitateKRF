#ifndef FIGHT_SCENE_H
#define FIGHT_SCENE_H

#include "cocos2d.h"
#include "Battlefield.h"
#include "GameUI.h"

USING_NS_CC;

class FightScene: public Layer {
public:
	FightScene();
	~FightScene();

	CC_SYNTHESIZE(int, level_, Level);

	CREATE_FUNC(FightScene);

	bool init() override;

private:
	Battlefield *battle_field_;
	GameUI *ui_;
	enum ZORDER {
		BATTLEFIELD, GAME_UI
	};
};

#endif

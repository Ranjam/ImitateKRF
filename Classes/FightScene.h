#ifndef FIGHT_SCENE_H
#define FIGHT_SCENE_H

#include "cocos2d.h"
#include "Monster.h"
#include "WarningFlag.h"
#include "BaseMap.h"
#include "GameUI.h"

USING_NS_CC;

class FightScene: public Layer {
public:
	FightScene();
	~FightScene();

	CC_SYNTHESIZE(int, level_, Level);

	CREATE_FUNC(FightScene);

	bool init() override;

	void loadMonsterData();

	void loadPathData();

	// todo: wave func
	void updateWaves(float dt);
	// todo: monster func
	void addMonsters(float dt);

private:
	// all monsters
	std::vector<std::vector<Vector<Monster *>>> monsters_;
	// monster's paths
	std::vector<std::vector<std::vector<Vec2>>> monster_paths_;
	// wave flags
	Vector<WarningFlag *> warning_flags_;

	int start_gold_;
	int start_life_;
	int max_wave_;

	int current_wave_;

private:
	BaseMap *map_;
	GameUI *ui_;
	enum ZORDER {
		MAP, GAME_UI
	};
};

#endif

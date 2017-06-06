#ifndef __MONSTER_LAYER_H__
#define __MONSTER_LAYER_H__

#include "Monster.h"
#include "cocos2d.h"

USING_NS_CC;

class MonsterLayer: public Layer {
public:
	struct MonsterInfo {
		int type;
		int path;
	};

	MonsterLayer();
	~MonsterLayer();

	CREATE_FUNC(MonsterLayer);

	bool init() override;

	void nextWave();

	void loadLevelData();

	Monster *generateMonster(int type, int path);

	void monsterIncoming(float dt);

	bool waveIsOver() const {
		return wave_over_;
	}

	bool allOver() const {
		return current_wave_ == monster_info_.size();
	}

private:
	// monster's paths
	std::vector<std::vector<Vec2>> paths_;

	// all monsters infomation
	std::vector<std::vector<MonsterInfo>> monster_info_;

	int current_wave_ = 0;
	int current_monster_ = 0;
	bool wave_over_ = true;
};

#endif

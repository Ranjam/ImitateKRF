#ifndef __MONSTER_LAYER_H__
#define __MONSTER_LAYER_H__

#include "Monster.h"
#include "cocos2d.h"
#include "GameManager.h"

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

	Monster *generateMonster(int type, int path);

	void monsterIncoming(float dt);

	bool waveIsOver() const {
		return wave_over_;
	}

	bool allOver() const {
		return GameManager::getInstance()->getCurrentWave() == GameManager::getInstance()->getWaveCount();
	}

	std::vector<std::vector<MonsterInfo>> &getMonsterInfo() {
		return monster_info_;
	}

	std::vector<std::vector<Vec2>> &getPaths() {
		return paths_;
	}

private:
	// monster's paths
	std::vector<std::vector<Vec2>> paths_;

	// all monsters infomation
	std::vector<std::vector<MonsterInfo>> monster_info_;

	unsigned int current_monster_ = 0;
	bool wave_over_ = true;
};

#endif

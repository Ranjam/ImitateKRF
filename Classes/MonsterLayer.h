#ifndef MONSTER_LAYER_H
#define MONSTER_LAYER_H

#include "Monster.h"
#include "cocos2d.h"
#include "WarningFlag.h"

USING_NS_CC;

class MonsterLayer: public Layer {
public:
	MonsterLayer();
	~MonsterLayer();

	CREATE_FUNC(MonsterLayer);

	bool init() override;

	void loadPathData();

	void loadMonstersData();

	void nextWave(float dt);

	Monster *generateMonster(int type, int path, int road);

	bool waveIsOver() const {
		return wave_over_;
	}

private:
	// monster's paths
	std::vector<std::vector<std::vector<Vec2>>> monster_paths_;

	// all monsters
	std::vector<std::vector<Vector<Monster *>>> monsters_;
	int current_frame_ = 0;
	int current_wave_ = 0;
	bool wave_over_ = true;
};

#endif

#pragma once

#ifndef BASE_MAP
#define BASE_MAP

#include "cocos2d.h"
#include "Monster.h"

USING_NS_CC;

class BaseMap: public Layer {
public:
	BaseMap();
	~BaseMap();

	CC_SYNTHESIZE(int, level_, Level);

	CREATE_FUNC(BaseMap);

	bool init() override;

	void loadMonsterData();

	void loadPathData();

private:
	std::vector<std::vector<Vector<Monster *>>> monsters_;
	std::vector<std::vector<std::vector<Vec2>>> monster_paths_;
	std::string start_gold_;
	std::string start_life_;
	std::string start_wave_;
};

#endif

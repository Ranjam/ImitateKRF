#ifndef __Battlefiled_H__
#define __Battlefiled_H__

#include "cocos2d.h"
#include "BaseMap.h"
#include "MonsterLayer.h"

USING_NS_CC;

class Battlefield: public Layer {
public:
	Battlefield();
	~Battlefield();

	static Battlefield* create(int level) {
		Battlefield *pRet = new(std::nothrow) Battlefield(); 
		if (pRet && pRet->init(level)) {
			pRet->autorelease(); 
			return pRet;
		}
		delete pRet;
		return nullptr;
	};

	bool init(int level);

	void nextWave();

	void waveOver();

	void loadLevelData(int level);

private:
	BaseMap *map_;
	MonsterLayer *monster_layer_;
	std::vector<Vec2> warning_flags_info_;

private:
	enum Tag {
		WARNING_FLAG = 0
	};
	enum Zorder {
		MAP = -1,
		MONSTER_LAYER = 1
	};
};

#endif

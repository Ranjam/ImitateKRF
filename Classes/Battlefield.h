#ifndef Battlefield_H
#define Battlefiled_H

#include "cocos2d.h"
#include "BaseMap.h"
#include "MonsterLayer.h"

USING_NS_CC;

class Battlefield: public Layer {
public:
	enum Tag {
		WARNING_FLAG = 0
	};
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
		pRet = nullptr;
		return nullptr;
	};

	bool init(int level);

	void nextWave();

	void waveOver();

	void loadLevelData();

private:
	BaseMap *map_;
	MonsterLayer *monster_layer_;
	std::vector<Vec2> warning_flags_info_;
};

#endif

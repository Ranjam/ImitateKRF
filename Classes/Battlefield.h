#ifndef Battlefield_H
#define Battlefiled_H

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
		pRet = nullptr;
		return nullptr;
	};

	bool init(int level);

	void updateWave(float dt);

	void updateFlag(float dt);

private:
	BaseMap *map_;
	MonsterLayer *monster_layer_;

	// wave flags
	Vector<WarningFlag *> warning_flags_;
};

#endif
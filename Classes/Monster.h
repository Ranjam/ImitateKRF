#pragma once

#ifndef MONSTER
#define MONSTER

#include "cocos2d.h"

USING_NS_CC;

class Monster: public Node {
public:
	Monster();
	~Monster();

	static Monster* create(int type, int road, int path) {
		Monster *pRet = new(std::nothrow) Monster(); 
		if (pRet && pRet->initMonster(type, road, path)) {
			pRet->autorelease(); 
			return pRet;
		}
		delete pRet; 
		pRet = nullptr; 
		return nullptr;
	};

	bool initMonster(int type, int road, int path);

	// 保存怪物类型
	CC_SYNTHESIZE(int, type, Type);

	// 不同出口  
	CC_SYNTHESIZE(int, road, Road);

	// 不同路线  
	CC_SYNTHESIZE(int, path, Path);
};

#endif

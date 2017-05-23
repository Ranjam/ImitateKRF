#ifndef BASE_MAP_H
#define BASE_MAP_H

#include "cocos2d.h"

USING_NS_CC;

class BaseMap: public Layer {
public:
	BaseMap();
	~BaseMap();

	static BaseMap* create(int level) {
		BaseMap *pRet = new(std::nothrow) BaseMap(); 
		if (pRet && pRet->init(level)) {
			pRet->autorelease(); 
			return pRet;
		}
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};

	bool init(int level);
};

#endif
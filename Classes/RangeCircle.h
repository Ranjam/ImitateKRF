#ifndef __RANGE_CIRCLE_H__
#define __RANGE_CIRCLE_H__

#include "cocos2d.h"

USING_NS_CC;

class RangeCircle: public Sprite {
public:
	enum RangeType {
		RANGE, RALLY
	};
public:
	RangeCircle();
	~RangeCircle();

public:
	static RangeCircle* create(RangeType type, unsigned int scope) {
		RangeCircle *pRet = new(std::nothrow) RangeCircle(); 
		if (pRet && pRet->init(type, scope)) {
			pRet->autorelease(); 
			return pRet;
		}
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

	bool init(RangeType type, unsigned int scope);
};

#endif

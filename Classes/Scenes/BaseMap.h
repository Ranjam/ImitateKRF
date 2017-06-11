#ifndef __BASE_MAP_H__
#define __BASE_MAP_H__

#include "cocos2d.h"

USING_NS_CC;

class BaseMap: public Layer {
public:
	BaseMap();
	~BaseMap();

	static BaseMap* create(int level) {
		BaseMap* pRet = new(std::nothrow) BaseMap();
		if (pRet && pRet->init(level)) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};

	bool init(int level);

	const Size &getMapSize() const {
		return map_->getContentSize();
	}

private:
	Sprite *map_;
};

#endif
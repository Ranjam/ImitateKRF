#ifndef DESERT_THUG_H
#define DESERT_THUG_H

#include "Monster.h"

class DesertThug: public Monster {
public:
	DesertThug();
	~DesertThug();

	static DesertThug* create(int type, const std::vector<Vec2> &path) {
		DesertThug *pRet = new(std::nothrow) DesertThug(); 
		if (pRet && pRet->init(type, path)) {
			pRet->autorelease(); 
			return pRet;
		}
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}

	bool init(int type, const std::vector<Vec2> &path);

	void update(float dt) override;

	void setState(MonsterState state) override;

	void dying() override;

};

#endif

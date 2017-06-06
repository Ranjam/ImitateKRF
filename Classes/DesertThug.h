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

	bool init(int type, const std::vector<Vec2> &path) override;

	void update(float dt) override;

	void setState(MonsterState state) override;

	void keepGoing() override;

	void dying() override;

private:
	int current_target_point_ = 1; // current point
	float speed_ = 25.0f;
};

#endif

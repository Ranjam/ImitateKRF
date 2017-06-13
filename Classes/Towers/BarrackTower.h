#ifndef __BASE_TOWER_H__
#define __BASE_TOWER_H__

#include "BaseTower.h"

class BarrackTower: public BaseTower {
public:
	BarrackTower();
	~BarrackTower();

	static BarrackTower* create() {
		auto pRet = new(std::nothrow) BarrackTower();
		if (pRet && pRet->init()) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		return nullptr;
	}

	bool init() override;

	void attack(float dt) override {}
	void upgradeTower() override {}
	void sellTower() override {}
	void removeTower() override {}
	void showTowerInfo() override {}
	void hideTowerInfo() override {}
	void upgradeOne() override {}
	void upgradeTwo() override {}
	void setRallyPoint(Vec2 pos) override {}
	void buildingAnimation() override {}
	void buildingSmokeAnimation() override {}

protected:
	void initTower(int level) override {}

public:
	static const float kBarrackTowerLv1Scope;
	static const float kBarrackTowerLv2Scope;
	static const float kBarrackTowerLv3Scope;
};

#endif

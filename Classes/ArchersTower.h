#ifndef ARCHERS_TOWER_H
#define ARCHERS_TOWER_H

#include "BaseTower.h"

class ArchersTower: public BaseTower {
public:
	ArchersTower();
	~ArchersTower();

	CREATE_FUNC(ArchersTower);

	bool init() override;

public:
	void attack(float dt) override;
	virtual void upgradeTower() {};
	virtual void sellTower() {};
	virtual void removeTower() {};
	void showTowerInfo() override;
	void hideTowerInfo() override;
	virtual void upgradeOne() {};
	virtual void upgradeTwo() {};
	virtual void setRallyPoint(Vec2 pos) {};

	void buildingAnimation() override;
	void buildingSmokeAnimation() override;
	void initTower(int level) override;

private:
	void addTouchListener();

private:
	Sprite *tower_base_ = nullptr;
	Sprite *archer_left_ = nullptr;
	Sprite *archer_right_ = nullptr;
	int current_archer_ = 0;
	bool info_is_shown = false;

public:
	static const float kArcherTowerLv1Scope;
	static const float kArcherTowerLv2Scope;
	static const float kArcherTowerLv3Scope;
};

#endif

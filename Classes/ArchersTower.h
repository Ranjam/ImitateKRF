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
	virtual void upgradeTower() {};
	virtual void sellTower() {};
	virtual void removeTower() {};
	virtual void showTowerInfo() {};
	virtual void upgradeOne() {};
	virtual void upgradeTwo() {};
	virtual void setRallyPoint(Vec2 pos) {};

	void buildingAnimation() override;
	void buildingSmokeAnimation() override;
	void initTower(int level) override;

private:
	Sprite *tower_base_ = nullptr;
	Sprite *archer_left_ = nullptr;
	Sprite *archer_right_ = nullptr;
};

#endif

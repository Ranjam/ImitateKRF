#ifndef ARCHERS_TOWER_H
#define ARCHERS_TOWER_H

#include "BaseTower.h"

class ArchersTower: public BaseTower {
public:
	ArchersTower();
	~ArchersTower();

	bool init() override;

public:
	virtual void upgradeTower() = 0;
	virtual void sellTower() = 0;
	virtual void removeTower() = 0;
	virtual void showTowerInfo() = 0;
	virtual void upgradeOne() = 0;
	virtual void upgradeTwo() = 0;
	virtual void setRallyPoint(Vec2 pos) = 0;
};

#endif

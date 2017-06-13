#include "BarrackTower.h"

const float BarrackTower::kBarrackTowerLv1Scope = 150.0f;
const float BarrackTower::kBarrackTowerLv2Scope = 200.0f;
const float BarrackTower::kBarrackTowerLv3Scope = 250.0f;

BarrackTower::BarrackTower(): BaseTower(
	TowerType::BARRACK,  // type
	"Barrack Tower",	// name
	1, // level
	kBarrackTowerLv1Scope, // scope
	kBarrackTowerLv2Scope, // next scope
	1.0f, // rate
	20.0f, // power
	20, // upgrade price
	10, // selling price
	nullptr // target monster
) { }


BarrackTower::~BarrackTower() {
}

bool BarrackTower::init() {
	if (!BaseTower::init()) {
		return false;
	}

	return true;
}

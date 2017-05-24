#include "BattlefieldUI.h"
#include "Common.h"


BattlefieldUI::BattlefieldUI() {
}


BattlefieldUI::~BattlefieldUI() {
}

bool BattlefieldUI::init() {
	if (!Layer::init()) {
		return false;
	}

	return true;
}

void BattlefieldUI::addWarningFlags(float x, float y) {
	auto flag = WarningFlag::create();
	flag->setPosition(x, y);
	this->addChild(flag);
	flag->start();
	warning_flags_.pushBack(flag);
}

#ifndef BATTLEFIELD_UI_H
#define BATTLEFIELD_UI_H

#include "cocos2d.h"
#include "WarningFlag.h"

USING_NS_CC;

class BattlefieldUI: public Layer {
public:
	BattlefieldUI();
	~BattlefieldUI();

	CREATE_FUNC(BattlefieldUI);

	bool init() override;

	void addWarningFlags(float x, float y);

private:
	// wave flags
	Vector<WarningFlag *> warning_flags_;
};

#endif

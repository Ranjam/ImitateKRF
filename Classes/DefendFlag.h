#ifndef __DEFEND_FLAG__
#define __DEFEND_FLAG__

#include "cocos2d.h"

USING_NS_CC;

class DefendFlag: public Sprite {
public:
	DefendFlag();
	~DefendFlag();

	CREATE_FUNC(DefendFlag);

	bool init() override;

	void update(float dt) override;
};

#endif

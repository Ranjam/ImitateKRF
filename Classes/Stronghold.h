#ifndef	STRONGHOLD_H
#define STRONGHOLD_H

#include "cocos2d.h"
#include "RingPanel.h"

USING_NS_CC;

class Stronghold: public Sprite {
public:
	Stronghold();
	~Stronghold();

	CREATE_FUNC(Stronghold);

	bool init() override;

private:
	RingPanel *ring_panel_;
};

#endif

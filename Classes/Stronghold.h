#ifndef	STRONGHOLD_H
#define STRONGHOLD_H

#include "cocos2d.h"
#include "RingPanel.h"
#include "BaseTower.h"

USING_NS_CC;

class Stronghold: public Sprite {
public:
	Stronghold();
	~Stronghold();

	CREATE_FUNC(Stronghold);

	bool init() override;

	void showPreview(BaseTower::TowerType tower_type);

	void hidePreview();

private:
	RingPanel *ring_panel_;
	Sprite *preview_ = nullptr;
};

#endif

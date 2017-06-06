#ifndef	STRONGHOLD_H
#define STRONGHOLD_H

#include "cocos2d.h"
#include "RingPanel.h"
#include "BaseTower.h"
#include "RangeCircle.h"

USING_NS_CC;

class Stronghold: public Sprite {
public:
	Stronghold();
	~Stronghold();

	CREATE_FUNC(Stronghold);

	bool init() override;

	void showPreview(BaseTower::TowerType tower_type);

	void hidePreview();

	void buildTower(BaseTower::TowerType tower_type);

	void removeTower();

	void addRangeCircle(RangeCircle::RangeType type, float scope) {
		if (!range_circle_added_) {
			this->addChild(RangeCircle::create(type, scope), -1, 999);
			range_circle_added_ = true;
		}
	}

	void removeRangeCircle() {
		if (range_circle_added_) {
			this->removeChildByTag(999, true);
			range_circle_added_ = false;
		}
	}

private:
	// stronghold background
	Sprite *image_ = nullptr;
	// ring panel
	RingPanel *ring_panel_ = nullptr;
	// tower preview
	Sprite *preview_ = nullptr;
	// tower
	BaseTower *tower_ = nullptr;
	// range circle is added
	bool range_circle_added_ = false;
};

#endif

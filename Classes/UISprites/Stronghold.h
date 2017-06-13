#ifndef	__STRONGHOLD_H__
#define __STRONGHOLD_H__

#include "cocos2d.h"
#include "RingPanel.h"
#include "RangeCircle.h"
#include "Towers/BaseTower.h"

USING_NS_CC;

class Stronghold: public Sprite {
private:
	enum Zorder {
		BACKGROUND, TOWER, RANGE_CIRCLE, RING_PANEL
	};
public:
	Stronghold();
	~Stronghold();

	static Stronghold* create() {
		auto pRet = new(std::nothrow) Stronghold();
		if (pRet && pRet->init()) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		return nullptr;
	};

	bool init() override;

	void showPreview(BaseTower::TowerType tower_type);

	void hidePreview();

	void buildTower(BaseTower::TowerType tower_type);

	void removeTower();

	void addRangeCircle(RangeCircle::RangeType type, float scope);

	void removeRangeCircle();

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

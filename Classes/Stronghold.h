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

	void buildTower(BaseTower::TowerType tower_type);

	void removeTower();

private:
	// stronghold background
	Sprite *image_ = nullptr;
	// ring panel
	RingPanel *ring_panel_ = nullptr;
	// tower preview
	Sprite *preview_ = nullptr;
	// tower
	BaseTower *tower_ = nullptr;
};

#endif

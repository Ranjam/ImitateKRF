#ifndef ARCHERS_TOWER_ICON_H
#define ARCHERS_TOWER_ICON_H

#include "BaseIcon.h"

USING_NS_CC;

class ArchersTowerIcon: public BaseIcon {
public:
	ArchersTowerIcon();
	~ArchersTowerIcon();

	CREATE_FUNC(ArchersTowerIcon);

	bool init() override;

	void onConfirmed() override;

	void onClicked() override;
};

#endif
#ifndef __ARCHERS_TOWER_ICON_H__
#define __ARCHERS_TOWER_ICON_H__

#include "BaseIcon.h"

USING_NS_CC;

class ArchersTowerIcon: public BaseIcon {
public:
	ArchersTowerIcon();
	~ArchersTowerIcon();

	CREATE_FUNC(ArchersTowerIcon);

	bool init() override;

	void onClicked() override;

	void onCanceled() override;

	void onConfirmed() override;
};

#endif

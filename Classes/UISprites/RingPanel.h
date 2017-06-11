#ifndef __RING_PANEL_H__
#define __RING_PANEL_H__

#include "cocos2d.h"
#include "Icon/BaseIcon.h"

USING_NS_CC;

class RingPanel: public Sprite {
public:
	RingPanel();
	~RingPanel();

	CREATE_FUNC(RingPanel);

	bool init() override;

	void show();

	void hide();

	bool isShow() const {
		return is_shown_;
	}

	void addIcon(BaseIcon *icon, float x, float y);

	void clearIcons();

private:
	bool is_shown_ = false;
	Vector<BaseIcon *> icons_;
};

#endif

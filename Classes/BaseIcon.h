#ifndef BASE_ICON_H
#define BASE_ICON_H

#include "cocos2d.h"

USING_NS_CC;

class BaseIcon: public Sprite {
public:
	BaseIcon();
	~BaseIcon();

	CREATE_FUNC(BaseIcon);

	bool init() override;

	virtual void onConfirmed() {
		confirm_->setVisible(false);
	}

	virtual void onClicked() {
		confirm_->setVisible(true);
	}

protected:
	Sprite *image_;
	Sprite *confirm_;
	bool selected_ = false;
};

#endif

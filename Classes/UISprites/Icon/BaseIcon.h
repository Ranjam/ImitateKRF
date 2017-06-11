#ifndef __BASE_ICON_H__
#define __BASE_ICON_H__

#include "cocos2d.h"

USING_NS_CC;

class BaseIcon: public Sprite {
public:
	BaseIcon();
	~BaseIcon();

	CREATE_FUNC(BaseIcon);

	bool init() override;

	virtual void onClicked() { }

	virtual void onCanceled() { }

	virtual void onConfirmed() { }


protected:
	Sprite *image_;
	Sprite *confirm_;
	bool selected_ = false;
};

#endif

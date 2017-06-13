#ifndef __BASE_ICON_H__
#define __BASE_ICON_H__

#include "cocos2d.h"

USING_NS_CC;

class BaseIcon: public Sprite {
public:
	enum IconType {
		ARCHERS_TOWER, BARRACK_TOWER, MAGE_TOWER, ARTILLERY_TOWER, NONE
	};

private:
	enum Zorder {
		BACKGROUND, FOREGROUND, CONFIRM
	};

public:
	BaseIcon();
	~BaseIcon();

	static BaseIcon* create(IconType type) {
		BaseIcon* pRet = new(std::nothrow) BaseIcon();
		if (pRet && pRet->init(type)) {
			pRet->autorelease();
			return pRet;
		}
		else {
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	};

	virtual bool init(IconType type);

	virtual void onClicked();

	virtual void onCanceled();

	virtual void onConfirmed();


protected:
	Sprite *background;
	Sprite *image_;
	Sprite *confirm_;
	bool selected_ = false;
	IconType icon_type_;
};

#endif

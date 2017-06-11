#ifndef __WELCOME_SLOT_MENU__
#define __WELCOME_SLOT_MENU__

#include "cocos2d.h"

USING_NS_CC;

class WelcomeSlotMenu: public Sprite {
public:
	WelcomeSlotMenu();
	~WelcomeSlotMenu();

	bool init() override;
	
	static WelcomeSlotMenu* create() {
		WelcomeSlotMenu* pRet = new(std::nothrow) WelcomeSlotMenu();
		if (pRet && pRet->init()) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};

private:
	enum Tag {
		BACKGROUND, SLOT01 = 1, SLOT02, SLOT03
	};

	enum Zorder {
		BG = -1, SPRITES = 1, LABEL = 2
	};

	void setSlotDisplay(Tag slot_tag, const char *save_name);
	void showNewGame(Tag slot_tag);
	void showSaveData(Tag slot_tag);
	void showSelect(Tag slot_tag);
	void bindEventOneByOne(Tag slot_tag);
	void bindDeleteEvent(Tag slot_tag);
};

#endif

#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class WelcomeScene: public Layer {
public:
	static Scene* createScene();

	bool init() override;

	void logoAnimationCallback(float dt);

	void startButtonAnimationCallback(float dt);
	void creditsButtonAnimationCallback();

	void setSaveSlotMenu();

	static WelcomeScene* create() {
		WelcomeScene* pRet = new(std::nothrow) WelcomeScene();
		if (pRet && pRet->init()) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		return nullptr;
	}

private:
	enum Tag {
		START_BUTTON, CREDITS_BUTTON, CLOSE_BUTTON, SLOT_MENU
	};

	enum Zorder {
		BACKGROUND = -2,
		CREDITS = -1,
		START = 0,
		SIMPLE_UI = 1,
		LOGO = 2
	};
};

#endif // __WELCOME_SCENE_H__

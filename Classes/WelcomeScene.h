#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class WelcomeScene: public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	void logoAnimationCallback(float dt);

	void startButtonAnimationCallback(float dt);

	void setSaveSlotMenu();

	static WelcomeScene* create() {
		WelcomeScene *pRet = new(std::nothrow) WelcomeScene(); 
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
		START_BUTTON, CLOSE_BUTTON, SLOT_MENU
	};
};

#endif // __HELLOWORLD_SCENE_H__

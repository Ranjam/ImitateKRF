#ifndef __CREDITS_SCENE_H__
#define __CREDITS_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class CreditsScene: public Layer {
public:
	CreditsScene();
	~CreditsScene();

	static Scene *createScene() {
		auto scene = Scene::create();

		auto layer = CreditsScene::create();

		scene->addChild(layer);

		return scene;
	}

	CREATE_FUNC(CreditsScene);

	bool init() override;
};

#endif

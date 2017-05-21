#ifndef GAME_UI_H
#define GAME_UI_H

#include "cocos2d.h"

USING_NS_CC;

class GameUI: public Layer {
public:
	GameUI();
	~GameUI();

	CREATE_FUNC(GameUI);

	bool init() override;

	// fire skill set and update
	void setMeteor();

	void updateMeteor(float dt);

private:
	EventListenerTouchOneByOne *select_target_;
	bool on_meteor_ = false;

private:
	enum Tag {
		METEOR_BG, METEOR_PROG, SOLDIER_BG, SOLDIER_PROG
	};
};

#endif

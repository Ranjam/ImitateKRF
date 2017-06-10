#ifndef __SKILL_H__
#define __SKILL_H__

#include "cocos2d.h"

USING_NS_CC;

class Skill: public Sprite {
public:
	Skill();
	~Skill();

	virtual bool init(std::string normal, std::string active);

	bool isClicked() const {
		return is_clicked_;
	}

	bool isReady() const {
		return is_ready_;
	}

	const Sprite *getImage() const {
		return image_;
	}

	void onClick();
	void undoClick();

	void coolDown(float time);
	void processCoolDown(float dt);

	virtual void execute(Touch *touch, Event *event) = 0;

private:
	bool is_clicked_;
	bool is_ready_;
	ProgressTimer *progress_timer_;
	Sprite *image_;
	SpriteFrame *normal_image_;
	SpriteFrame *active_image_;
	EventListenerTouchOneByOne *select_target_;
};

#endif

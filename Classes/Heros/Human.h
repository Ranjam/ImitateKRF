#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "cocos2d.h"
#include "Monsters/Monster.h"

USING_NS_CC;

class Human: public Sprite {
public:
	Human();
	~Human();

	bool init(int type, int hp, int max_hp, float scope, SpriteFrame *sprite_frame);

public:
	CC_SYNTHESIZE(int, type_, Type);

	CC_SYNTHESIZE(int, hp_, HP);

	CC_SYNTHESIZE(int, max_hp_, MaxHP);

	CC_SYNTHESIZE(float, scope_, Scope);

	CC_SYNTHESIZE(Sprite *, image_, Image);

protected:
	void checkMonster();

protected:
	Monster *target_monster_ = nullptr;
};

#endif

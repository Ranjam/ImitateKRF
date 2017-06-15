#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "cocos2d.h"

USING_NS_CC;

class Creature: public Sprite {
public:
	enum HP_Type {
		SMALL, MIDDLE, BIG
	};
public:
	Creature();
	~Creature();

	bool init(int hp, int max_hp, float speed, float scope, bool is_removed, SpriteFrame *image, HP_Type hp_type);

protected:
	// HP
	CC_SYNTHESIZE(int, hp_, HP);

	// MAX HP
	CC_SYNTHESIZE(int, max_hp_, MaxHP);

	// speed
	CC_SYNTHESIZE(float, speed_, Speed);

	// scope
	CC_SYNTHESIZE(float, scope_, Scope);

	// is removed
	CC_SYNTHESIZE(bool, is_removed_, IsRemoved);

protected:
	Creature * target_;

public:
	virtual Creature * getTarget(void) const {
		return target_;
	}

	virtual void setTarget(Creature * var) {
		target_ = var;
		target_->retain();
	}

	virtual void releaseTarget() {
		target_->release();
		target_ = nullptr;
	}

	virtual void getDamage(float damage);

	virtual void dying() = 0;

	Sprite *getImage() const {
		return image_;
	}

protected:
	Sprite *image_;
	Sprite *hp_bg_;
	ProgressTimer *hp_prog_;
};

#endif

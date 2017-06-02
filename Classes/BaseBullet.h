#ifndef __BASE_BULLET_H__
#define __BASE_BULLET_H__

#include "cocos2d.h"

USING_NS_CC;

class BaseBullet: public Sprite {
public:
	BaseBullet();
	~BaseBullet();

	bool init() override;

protected:
	// power
	CC_SYNTHESIZE(float, power_, Power);  

	// bullet animation
	CC_SYNTHESIZE(Spawn*, bullet_animation_, BulletAnimation);

public:
	// attack
	virtual void attack() = 0;

	// destroy
	virtual void destroy() = 0;
};

#endif

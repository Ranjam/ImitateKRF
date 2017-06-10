#ifndef __FIRE_BALL_BULLET_H__
#define __FIRE_BALL_BULLET_H__

#include "BaseBullet.h"

class FireballBullet: public BaseBullet {
public:
	FireballBullet();
	~FireballBullet();

	CREATE_FUNC(FireballBullet);

	bool init() override;

	void attack() override;
	void destroy() override;

	void particleEffect(float dt);
	void explode();

private:
	Sprite *fire_ball_;
};

#endif

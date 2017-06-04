#ifndef __ARROW_BULLET_H__
#define __ARROW_BULLET_H__

#include "BaseBullet.h"

class ArrowBullet: public BaseBullet {
public:
	ArrowBullet();
	~ArrowBullet();

	CREATE_FUNC(ArrowBullet);

	bool init() override;

	// attack
	void attack() override;

	// destroy
	void destroy() override;

	/**
	 * \brief execute parabola action move arrow to target
	 * \param delta_vec the target relative vector
	 * \param height the max height
	 * \param duration action duration time
	 * \param call_func when action finish do
	 */
	void shootBy(Vec2 delta_vec, float height, float duration, CallFunc *call_func);
};

#endif

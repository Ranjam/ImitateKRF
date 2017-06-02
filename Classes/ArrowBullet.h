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
};

#endif

#ifndef __FIRE_BALL_SKILL_H__
#define __FIRE_BALL_SKILL_H__

#include "Skill.h"

class FireBallSkill:public Skill {
public:
	FireBallSkill();
	~FireBallSkill();

	static FireBallSkill* create() {
		FireBallSkill* pRet = new(std::nothrow) FireBallSkill();
		if (pRet && pRet->init()) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		pRet = nullptr;
		return nullptr;
	};

	bool init() override;
	void execute(Touch* touch, Event* event) override;
	void Instantiate(float dt);

private:
	Vec2 origin_pos_;
};

#endif

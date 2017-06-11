#ifndef __REINFORCEMENT_SKILL_H__
#define __REINFORCEMENT_SKILL_H__

#include "Skill.h"

class ReinforcementSkill: public Skill {
public:
	ReinforcementSkill();
	~ReinforcementSkill();

	static ReinforcementSkill* create() {
		ReinforcementSkill* pRet = new(std::nothrow) ReinforcementSkill();
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
};

#endif

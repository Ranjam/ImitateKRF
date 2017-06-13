#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "Human.h"

class Soldier: public Human {
public:
	Soldier();
	~Soldier();

	static Soldier* create() {
		auto pRet = new(std::nothrow) Soldier();
		if (pRet && pRet->init()) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		return nullptr;
	}

	bool init() override;

	void chase(float dt);
	void attack(float dt);
};

#endif

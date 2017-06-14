#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "Human.h"

class Soldier: public Human {
public:
	enum ReinforceType {
		A, B, C
	};
public:
	Soldier();
	~Soldier();

	static Soldier* create(ReinforceType type) {
		auto pRet = new(std::nothrow) Soldier();
		if (pRet && pRet->init(type)) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		return nullptr;
	}

	bool init(ReinforceType type);

	void chase(float dt);
	void attack(float dt);

private:
	std::string name_;
};

#endif

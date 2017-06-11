#include "ReinforcementSkill.h"



ReinforcementSkill::ReinforcementSkill() {
}


ReinforcementSkill::~ReinforcementSkill() {
}

bool ReinforcementSkill::init() {
	if (!Skill::init("power_portrait_reinforcement_0001.png", "power_portrait_reinforcement_0002.png")) {
		return false;
	}

	return true;
}

void ReinforcementSkill::execute(Touch* touch, Event* event) {
	
}

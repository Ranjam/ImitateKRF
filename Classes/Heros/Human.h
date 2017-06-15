#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "Creature.h"

class Human: public Creature {
public:
	Human();
	~Human();

	bool init(int hp, int max_hp, float speed, float scope, bool is_removed, SpriteFrame *sprite_frame, HP_Type hp_type);

protected:
	void checkMonster();
};

#endif

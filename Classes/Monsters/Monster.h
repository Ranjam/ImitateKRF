#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Creature.h"

class Monster: public Creature {
public:
	enum MonsterState {
		WALK_LEFT,
		WALK_RIGHT,
		WALK_UP,
		WALK_DOWN,
		ATTACK_LEFT,
		ATTACK_RIGHT,
		STOP
	};
public:
	Monster();
	~Monster();

	bool init(int hp, int max_hp, float speed, float scope, bool is_removed, SpriteFrame* sprite_frame, HP_Type hp_type, int type, const std::vector<Vec2>& path);

	// monster type
	CC_SYNTHESIZE(int, type_, Type);

	// current state
	CC_SYNTHESIZE(MonsterState, state_, State);

public:
	virtual void keepGoing();

protected:
	std::vector<Vec2> path_;
	int current_target_point_ = 1; // current point
};

#endif

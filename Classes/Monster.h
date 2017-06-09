
#ifndef MONSTER
#define MONSTER

#include "cocos2d.h"

USING_NS_CC;

class Monster: public Sprite {
public:
	enum MonsterState {
		WALK_LEFT,
		WALK_RIGHT,
		WALK_UP,
		WALK_DOWN,
		ATTACK_LEFT,
		ATTACK_RIGHT,
		STAND,
		DEAD
	};
public:
	Monster();
	~Monster();

	// monster type
	CC_SYNTHESIZE(int, type_, Type);

	// speed
	CC_SYNTHESIZE(float, speed_, Speed);

	// HP
	CC_SYNTHESIZE(int, hp_, HP);

	// MAX HP
	CC_SYNTHESIZE(int, max_hp_, MaxHP);

	// current state
	CC_SYNTHESIZE(MonsterState, state_, State);

	// is removed
	CC_SYNTHESIZE(bool, is_removed_, IsRemoved);

	virtual bool init(int type, const std::vector<Vec2> &path, float speed, int hp, int max_hp, bool is_removed);

public:
	virtual void keepGoing();

	virtual void getDamage(float damage);

	virtual void dying() = 0;

	Sprite *getImage() const {
		return image_;
	}

protected:
	Sprite *image_;
	Sprite *hp_bg_;
	ProgressTimer *hp_prog_;
	std::vector<Vec2> path_;
	int current_target_point_ = 1; // current point
};

#endif

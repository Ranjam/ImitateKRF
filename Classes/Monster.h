
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

	//static Monster* create(int type, int road, int path) {
	//	Monster *pRet = new(std::nothrow) Monster();
	//	if (pRet && pRet->init(type, road, path)) {
	//		pRet->autorelease();
	//		return pRet;
	//	}
	//	delete pRet;
	//	pRet = nullptr;
	//	return nullptr;
	//}

	virtual bool init(int type, int road, const std::vector<Vec2> &path);

	// 怪物类型
	// CC_SYNTHESIZE(int, type_, Type);

	// 出口  
	// CC_SYNTHESIZE(int, road_, Road);

	// 路线
	// CC_SYNTHESIZE(int, path_, Path);

	// 血量
	CC_SYNTHESIZE(int, hp_, HP);

	// 当前状态
	CC_SYNTHESIZE(MonsterState, state_, State);
public:
	virtual void keepGoing() = 0;

protected:
	Sprite *image_;
	Sprite *hp_bg_;
	ProgressTimer *hp_prog_;
	std::vector<Vec2> path_;
};

#endif

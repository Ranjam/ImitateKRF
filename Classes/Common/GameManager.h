#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class Battlefield;
class MonsterLayer;

class GameManager {
public:
	static GameManager *getInstance() {
		static GameManager instance;
		return &instance;
	}

private:
	GameManager();
	GameManager(const GameManager &) = delete;
	GameManager &operator=(const GameManager &) = delete;
	~GameManager();

	CC_SYNTHESIZE(int, current_wave_, CurrentWave);
	CC_SYNTHESIZE(int, gold_, Gold);
	CC_SYNTHESIZE(int, life_, Life);
	CC_SYNTHESIZE(int, wave_count_, WaveCount);
	CC_SYNTHESIZE(Battlefield *, battlefield_, Battlefield);
	CC_SYNTHESIZE(MonsterLayer *, monster_layer_, MonsterLayer);
};

#endif

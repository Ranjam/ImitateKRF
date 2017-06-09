#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "cocos2d.h"
#include "Monster.h"

USING_NS_CC;

class GameManager {
public:
	static GameManager *getInstance() {
		static GameManager instance;
		return &instance;
	}

	Vector<Monster *> &getMonsters() {
		return monsters_;
	}
private:
	//void loadPathData();

	//void loadMonstersData();

private:
	GameManager();
	GameManager(const GameManager &) = delete;
	GameManager &operator=(const GameManager &) = delete;
	~GameManager();

	CC_SYNTHESIZE(int, current_wave_, CurrentWave);
	CC_SYNTHESIZE(int, gold_, Gold);
	CC_SYNTHESIZE(int, life_, Life);
	CC_SYNTHESIZE(int, wave_count_, WaveCount);
private:
	Vector<Monster *> monsters_;
};

#endif

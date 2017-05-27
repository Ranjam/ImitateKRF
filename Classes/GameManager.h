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

	Vector<Monster *> &Monsters() {
		// todo: load all monsters
		return monsters_;
	}

private:
	Vector<Monster *> monsters_;

private:
	GameManager();
	GameManager(const GameManager &) = delete;
	GameManager &operator=(const GameManager &) = delete;
	~GameManager();
};

#endif

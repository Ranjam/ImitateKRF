#ifndef GAME_UI_H
#define GAME_UI_H

#include "cocos2d.h"
#include "GameManager.h"
#include "Skill.h"

USING_NS_CC;

class GameUI: public Layer {
public:
	GameUI();
	~GameUI();

	CREATE_FUNC(GameUI);

	bool init() override;

	// set life
	void setLifeLabel(std::string life) const {
		life_label_->setString(life);
	}

	// set gold
	void setGoldLabel(std::string gold) const {
		gold_label_->setString(gold);
	}

	void addSkill(Skill *skill);

	// set wave
	void setWaveLabel(std::string wave) const {
		wave_label_->setString("WAVE " + wave + " / " + std::to_string(GameManager::getInstance()->getWaveCount()));
	}

	// reset onclicked skills to normal state
	void resetClickedSkills();

	void update(float dt) override;

private:
	std::vector<Skill *> skills_;

public:
	Label *life_label_;
	Label *gold_label_;
	Label *wave_label_;

private:
	enum Tag {
		METEOR_BG, METEOR_PROG, SOLDIER_BG, SOLDIER_PROG
	};
};

#endif

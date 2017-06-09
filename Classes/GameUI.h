#ifndef GAME_UI_H
#define GAME_UI_H

#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

struct SkillRecord {
	bool on_click;
	bool on_doing;
	ProgressTimer *progress_timer;
	Sprite *background;
	std::string normal_image;
	std::string active_image;
};

class GameUI: public Layer {
public:
	GameUI();
	~GameUI();

	CREATE_FUNC(GameUI);

	bool init() override;

	// fire skill set and update
	void addSkill(const char *skill_image, const char *skill_active_image);

	void updateSkills(float dt);

	void resetSkillsClick();

	// set life
	void setLifeLabel(std::string life) const {
		life_label_->setString(life);
	}

	// set gold
	void setGoldLabel(std::string gold) const {
		gold_label_->setString(gold);
	}

	// set wave
	void setWaveLabel(std::string wave) const {
		wave_label_->setString("WAVE " + wave + " / " + std::to_string(GameManager::getInstance()->getWaveCount()));
	}

	void update(float dt) override;

private:
	EventListenerTouchOneByOne *select_target_;

	std::vector<SkillRecord> skills;

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

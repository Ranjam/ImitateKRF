#ifndef GAME_UI_H
#define GAME_UI_H

#include "cocos2d.h"
#include "WarningFlag.h"

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

private:
	EventListenerTouchOneByOne *select_target_;

	std::vector<SkillRecord> skills;

private:
	enum Tag {
		METEOR_BG, METEOR_PROG, SOLDIER_BG, SOLDIER_PROG
	};
};

#endif

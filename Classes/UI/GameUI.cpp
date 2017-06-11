#include "GameUI.h"
#include "Common/CommonMacro.h"
#include "Skills/FireballSkill.h"
#include "Skills/ReinforcementSkill.h"

GameUI::GameUI() {
}

GameUI::~GameUI() {
}

bool GameUI::init() {

	if (!Layer::init()) {
		return false;
	}

	// set hud background
	auto hud_bg = Sprite::createWithSpriteFrameName("hud_background.png");
	hud_bg->setAnchorPoint(Vec2(0, 1));
	hud_bg->setPosition(20, winSize.height - 20);
	this->addChild(hud_bg);

	// life label
	life_label_ = Label::createWithTTF(std::to_string(GameManager::getInstance()->getLife()), "fonts/arial.ttf", 18);
	life_label_->setPosition(Point(hud_bg->getContentSize().width / 4, hud_bg->getContentSize().height / 4 * 3));
	hud_bg->addChild(life_label_);

	// gold label
	gold_label_ = Label::createWithTTF(std::to_string(GameManager::getInstance()->getGold()), "fonts/arial.ttf", 18);
	gold_label_->setPosition(Point(hud_bg->getContentSize().width / 4 * 3, hud_bg->getContentSize().height / 4 * 3));
	hud_bg->addChild(gold_label_);

	// wave label
	wave_label_ = Label::createWithTTF("WAVE 0 / " + std::to_string(GameManager::getInstance()->getWaveCount()), "fonts/arial.ttf", 18);
	wave_label_->setPosition(Point(hud_bg->getContentSize().width / 2, hud_bg->getContentSize().height / 5 + 1));
	hud_bg->addChild(wave_label_);

	// set skills
	addSkill(FireballSkill::create());
	addSkill(ReinforcementSkill::create());

	scheduleUpdate();

	return true;
}

void GameUI::addSkill(Skill *skill) {
	this->addChild(skill);
	skill->setPosition(skills_.size() * skill->getImage()->getContentSize().width + 10.0f, 10.0f);
	this->skills_.push_back(skill);
}

void GameUI::resetClickedSkills() {
	for (auto skill : this->skills_) {
		if (skill->isClicked()) {
			skill->undoClick();
		}
	}
}

void GameUI::update(float dt) {
	
	this->setLifeLabel(std::to_string(GameManager::getInstance()->getLife()));

	this->setGoldLabel(std::to_string(GameManager::getInstance()->getGold()));

	this->setWaveLabel(std::to_string(GameManager::getInstance()->getCurrentWave()));
}

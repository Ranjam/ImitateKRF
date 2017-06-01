#include "ArchersTower.h"



ArchersTower::ArchersTower():BaseTower(
	TowerType::ARCHER,
	"",
	1,
	20.0f,
	25.0f,
	3.0f,
	5.0f,
	20,
	10,
	nullptr
) { }

ArchersTower::~ArchersTower() {
}

bool ArchersTower::init() {
	if (!BaseTower::init()) {
		return false;
	}

	buildingAnimation();

	return true;
}

// play building animation
void ArchersTower::buildingAnimation() {
	auto constructing = Sprite::create();
	// the preview ruin of building
	auto ruin = Sprite::createWithSpriteFrameName("tower_constructing_0004.png");

	// loading process bar and its background
	auto buildingbar_bg = Sprite::createWithSpriteFrameName("buildbar_bg.png");
	buildingbar_bg->setPosition(Vec2(ruin->getContentSize().width / 2, ruin->getContentSize().height / 1.5));
	auto buildingbar = ProgressTimer::create(Sprite::createWithSpriteFrameName("buildbar.png"));
	buildingbar->setType(ProgressTimer::Type::BAR);
	buildingbar->setMidpoint(Vec2(0, 0.5f));
	buildingbar->setBarChangeRate(Vec2(1.0f, 0));
	buildingbar->setPercentage(0);
	buildingbar->setPosition(Vec2(buildingbar_bg->getContentSize().width / 2, buildingbar_bg->getContentSize().height / 2));
	buildingbar_bg->addChild(buildingbar);
	ruin->addChild(buildingbar_bg);
	constructing->addChild(ruin);

	this->addChild(constructing, 1);

	// todo: why can not remove the last animation
	buildingbar->runAction(Sequence::create(ProgressTo::create(1.0f, 100)
										  , CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParentAndCleanup, constructing, true))
									      , CallFunc::create(CC_CALLBACK_0(ArchersTower::buildingSmokeAnimation, this)), NULL));
}

void ArchersTower::buildingSmokeAnimation() {
	// smoke effect
	auto smoke = Sprite::createWithSpriteFrameName("effect_buildSmoke_0001.png");
	this->addChild(smoke, 1);

	smoke->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("building_smoke_effect")),
									  CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParentAndCleanup, smoke, true)),
									  NULL));

	initTower(1);
}

void ArchersTower::initTower(int level) {
	// set the name
	this->setName(StringUtils::format("Archers Tower Level%02d", level));

	// set the tower base
	this->tower_base_ = Sprite::createWithSpriteFrameName(StringUtils::format("archer_tower_000%d.png", level));

	// set the archer
	this->archer_left_ = Sprite::createWithSpriteFrameName(StringUtils::format("tower_archer_lvl%d_shooter_0001.png", level));
	archer_left_->setPosition(Vec2(tower_base_->getContentSize().width / 2 - 10, tower_base_->getContentSize().height / 2 + 18));
	tower_base_->addChild(archer_left_);

	this->archer_right_ = Sprite::createWithSpriteFrameName(StringUtils::format("tower_archer_lvl%d_shooter_0001.png", level));
	archer_right_->setPosition(Vec2(tower_base_->getContentSize().width / 2 + 10, tower_base_->getContentSize().height / 2 + 18));
	tower_base_->addChild(archer_right_);

	this->addChild(tower_base_);
}

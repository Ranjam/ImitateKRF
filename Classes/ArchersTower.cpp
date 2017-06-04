#include "ArchersTower.h"
#include "ArrowBullet.h"


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

	schedule(schedule_selector(ArchersTower::attack1), 1.0f);

	return true;
}

void ArchersTower::attack1(float dt) {

	checkNearestMonster();

	if (nearest_monster_ != nullptr) {

		auto arrow = ArrowBullet::create();
		this->addChild(arrow);
		arrow->setVisible(false);

		// get the tower(stronghold) and monster ralative vector
		Vec2 relative_tower = nearest_monster_->getPosition() - this->getParent()->getPosition();

		Sprite *archer;
		if (current_archer_ == 0) {
			archer = archer_left_;
		} else {
			archer = archer_right_;
		}

		// if the monster on the left
		if (relative_tower.x <= 0) {
			archer->setFlippedX(true);
		} else {
			archer->setFlippedX(false);
		}
		arrow->setPosition(archer->getPosition());

		// if the monster on the up
		Animate *archer_animate;
		if (relative_tower.y <= 0) {
			archer_animate = Animate::create(AnimationCache::getInstance()->getAnimation("archer_lv1_shoot_down"));
		}
		else {
			archer_animate = Animate::create(AnimationCache::getInstance()->getAnimation("archer_lv1_shoot_up"));
		}

		archer->runAction(Sequence::create(archer_animate,
										   CallFunc::create([=]() 
		{
			arrow->setVisible(true);
			arrow->shootBy(relative_tower, 150.0f, 0.8f, CallFunc::create([=]() {
				if (nearest_monster_->getBoundingBox().intersectsRect(arrow->getBoundingBox())) {

				} else {
					// if not hit
					arrow->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("decal_arrow.png"));
					arrow->runAction(Sequence::create(
						DelayTime::create(1.0f),
						FadeOut::create(0.3f),
						CallFunc::create(CC_CALLBACK_0(ArrowBullet::removeFromParentAndCleanup, arrow, true)),
						NULL)
					);
				}
			}));
		}),
										   NULL));

		// if you want shoot arrow at the same time with pull the bow
		//arrow->shootBy(relative_tower, 150.0f, 0.8f, CallFunc::create([=]() {
		//	if (nearest_monster_->getBoundingBox().intersectsRect(arrow->getBoundingBox())) {
		//	} else {
		//		// if not hit
		//		arrow->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("decal_arrow.png"));
		//		arrow->runAction(Sequence::create(
		//			DelayTime::create(1.0f),
		//			FadeOut::create(0.3f),
		//			CallFunc::create(CC_CALLBACK_0(ArrowBullet::removeFromParentAndCleanup, arrow, true)),
		//			NULL)
		//		);
		//	}
		//}));

		// change the archer
		current_archer_ = current_archer_ == 0 ? 1 : 0;
	}
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
	this->addChild(tower_base_);

	// set the archer
	this->archer_left_ = Sprite::createWithSpriteFrameName(StringUtils::format("tower_archer_lvl%d_shooter_0001.png", level));
	archer_left_->setPosition(Vec2(-10.0f, 18.0f));
	this->addChild(archer_left_);

	this->archer_right_ = Sprite::createWithSpriteFrameName(StringUtils::format("tower_archer_lvl%d_shooter_0001.png", level));
	archer_right_->setPosition(Vec2(10.0f, 18.0f));
	this->addChild(archer_right_);
}

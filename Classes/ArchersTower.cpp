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

		// get the tower(stronghold) and monster ralative vector
		Vec2 relative_tower = nearest_monster_->getPosition() - this->getParent()->getPosition();

		// init angle
		float start_angle;
		float end_angle;

		Sprite *archer;
		if (current_archer_ == 0) {
			archer = archer_left_;
		} else {
			archer = archer_right_;
		}

		// left
		if (relative_tower.x < 0) {
			// init angle
			Vec2 relative_archer = archer->convertToNodeSpace(nearest_monster_->getParent()->convertToWorldSpace(nearest_monster_->getPosition())).getNormalized();
			float theta = CC_RADIANS_TO_DEGREES(atan(relative_archer.y / relative_archer.x));
			theta = relative_archer.y > 0 ? 180 + theta : 180 - theta;
			arrow->setRotation(theta);
			// counter clock wise
			end_angle = (theta - 15) > 90 ? theta - 15 : 90;

			arrow->setPosition(archer->getPosition());
			archer->setFlippedX(true);
		}
		// right
		else {
			// init angle
			Vec2 relative_archer = archer->convertToNodeSpace(nearest_monster_->getParent()->convertToWorldSpace(nearest_monster_->getPosition())).getNormalized();
			float theta = CC_RADIANS_TO_DEGREES(atan(relative_archer.y / relative_archer.x));
			theta = relative_archer.y > 0 ? theta : -theta;
			arrow->setRotation(theta);
			// clock wise
			end_angle = theta + 15 > 90 ? 90 : theta + 15;

			arrow->setPosition(archer->getPosition());
			archer->setFlippedX(false);
		}
		// if the monster on the up
		if (relative_tower.y <= 0) {
			archer->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("archer_lv1_shoot_down")));
		} else {
			archer->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("archer_lv1_shoot_up")));
		}

		// set the bezier
		ccBezierConfig bezier;
		// two control point
		bezier.controlPoint_1 = Point(arrow->getPosition().x + relative_tower.x / 2, arrow->getPosition().y + 20);
		bezier.controlPoint_2 = Point(relative_tower.x, relative_tower.y + 20);
		bezier.endPosition = relative_tower;

		auto action = Spawn::create(BezierTo::create(1.0f, bezier), RotateTo::create(1.0f, end_angle), NULL);
		arrow->setBulletAnimation(action);
		arrow->attack();

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

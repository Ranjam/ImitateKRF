#include "ArchersTower.h"
#include "Bullets/ArrowBullet.h"
#include "UISprites/Stronghold.h"
#include "UISprites/RangeCircle.h"
#include "Common/GameManager.h"
#include "Scenes/MonsterLayer.h"

const float ArchersTower::kArcherTowerLv1Scope = 150.0f;
const float ArchersTower::kArcherTowerLv2Scope = 200.0f;
const float ArchersTower::kArcherTowerLv3Scope = 250.0f;

ArchersTower::ArchersTower(): BaseTower(
	TowerType::ARCHER,  // type
	"",	// name
	1, // level
	kArcherTowerLv1Scope, // scope
	kArcherTowerLv2Scope, // next scope
	1.0f, // rate
	20.0f, // power
	20, // upgrade price
	10, // selling price
	nullptr // target monster
) { }

ArchersTower::~ArchersTower() {
}

bool ArchersTower::init() {
	if (!BaseTower::init()) {
		return false;
	}

	buildingAnimation();

	schedule(schedule_selector(ArchersTower::attack), this->rate_);

	return true;
}

void ArchersTower::attack(float dt) {

	this->checkNearestMonster();

	if (nearest_monster_ != nullptr) {
		Monster *target_monster = this->nearest_monster_;
		auto arrow = ArrowBullet::create();
		this->addChild(arrow);
		arrow->setVisible(false);

		// get the tower(stronghold) and monster ralative vector
		Vec2 relative_tower = target_monster->getPosition() - this->getParent()->getPosition();

		Sprite *archer;
		if (current_archer_ == 0) {
			archer = archer_left_;
		} else {
			archer = archer_right_;
		}

		// monster relative to the archer
		Vec2 relative_archer = this->convertToNodeSpace(target_monster->getParent()->convertToWorldSpace(target_monster->getPosition())) - archer->getPosition();

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
			arrow->shootBy(relative_archer, 150.0f, 0.5f, CallFunc::create([=]() {

				for (auto monster : GameManager::getInstance()->getMonsterLayer()->getMonsters()) {
					Vec2 world_arrow_origin = monster->convertToNodeSpace(arrow->getParent()->convertToWorldSpace(arrow->getPosition()));
					Rect arrow_rect = Rect(world_arrow_origin.x,
										   world_arrow_origin.y,
										   arrow->getContentSize().width,
										   arrow->getContentSize().height);
					// if arrow hit monster
					if (monster->getImage()->getBoundingBox().intersectsRect(arrow_rect)) {
						monster->getDamage(this->power_);
						arrow->removeFromParentAndCleanup(true);
						return;
					}
				}
				// if not hit
				arrow->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("decal_arrow.png"));
				arrow->runAction(Sequence::create(
					DelayTime::create(1.0f),
					FadeOut::create(0.3f),
					CallFunc::create(CC_CALLBACK_0(ArrowBullet::removeFromParentAndCleanup, arrow, true)),
					NULL)
				);
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

void ArchersTower::showTowerInfo() {
	if (!info_is_shown) {
		static_cast<Stronghold *>(this->getParent())->addRangeCircle(RangeCircle::RANGE, ArchersTower::kArcherTowerLv1Scope);
		info_is_shown = true;
	}
}

void ArchersTower::hideTowerInfo() {
	if (info_is_shown) {
		static_cast<Stronghold *>(this->getParent())->removeRangeCircle();
		info_is_shown = false;
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

	// add listener
	this->addTouchListener();
}

void ArchersTower::addTouchListener() {
	auto touch_listener = EventListenerTouchOneByOne::create();

	touch_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (this->tower_base_->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			this->showTowerInfo();
			return true;
		} else {
			this->hideTowerInfo();
			return false;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this->tower_base_);
}

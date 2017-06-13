#include "DesertThug.h"
#include "Common/SoundManager.h"
#include "Common/Resources.h"

DesertThug::DesertThug() {
}

DesertThug::~DesertThug() {
}

bool DesertThug::init(int type, const std::vector<Vec2> &path) {
	if (!Monster::init(type,
					   path, 
					   18.0f, // speed
					   100, // hp
					   100, // max hp
					   false // is dead
					   )) {
		return false;
	}

	image_ = Sprite::createWithSpriteFrameName("desertThug_0067.png");
	image_->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(image_, -1);
	
	hp_bg_ = Sprite::createWithSpriteFrameName("lifebar_bg_small.png");
	hp_bg_->setPosition(0.0f, 40.0f);
	this->addChild(hp_bg_, 0);

	hp_prog_ = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_small.png"));
	hp_prog_->setType(ProgressTimer::Type::BAR);
	hp_prog_->setMidpoint(Vec2(0.0f, 0.5f));
	hp_prog_->setScaleY(1.5f);
	hp_prog_->setPercentage(100.0f);
	hp_prog_->setPosition(0.0f, 40.0f);
	this->addChild(hp_prog_, 1);

	return true;
}

void DesertThug::update(float dt) {
	// nothing to do
}

void DesertThug::setState(MonsterState state) {
	this->state_ = state;
	this->image_->stopActionByTag(0);
	Action *animationAct;
	switch (state) {

	case WALK_LEFT:
		this->image_->setFlippedX(true);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_forward")));
		break;
	case WALK_RIGHT:
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_forward")));
		break;
	case WALK_UP:
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_up")));
		break;
	case WALK_DOWN:
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_down")));
		break;
	case ATTACK_LEFT:
		this->image_->setFlippedX(true);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_attack")));
		break;
	case ATTACK_RIGHT:
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_attack")));
		break;
	case STOP:
		this->stopAllActions();
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_stand")));
		break;
	}
	animationAct->setTag(0);
	image_->runAction(animationAct);
}

void DesertThug::dying() {
	int rand = RandomHelper::random_int(1, 4);
	SoundManager::getInstance()->playEffect(StringUtils::format(s_human_dead, rand).c_str());

	this->image_->stopAllActions();
	this->stopAllActions();
	this->hp_bg_->setVisible(false);
	this->image_->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_dead")),
											 DelayTime::create(0.5f),
											 CallFunc::create([=](){
		this->setVisible(false);
		this->removeFromParent();
	}), NULL));
}

#include "DesertThug.h"

DesertThug::DesertThug() {
}

DesertThug::~DesertThug() {
}

bool DesertThug::init(int type, int road, const std::vector<Vec2> &path) {
	if (!Monster::init(type, road, path)) {
		return false;
	}

	image_ = Sprite::createWithSpriteFrameName("desertThug_0067.png");
	this->addChild(image_, -1);
	
	hp_bg_ = Sprite::createWithSpriteFrameName("lifebar_bg_small.png");
	hp_bg_->setPosition(0.0f, 20.0f);
	this->addChild(hp_bg_, 0);

	hp_prog_ = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_small.png"));
	hp_prog_->setType(ProgressTimer::Type::BAR);
	hp_prog_->setMidpoint(Vec2(0.0f, 0.5f));
	hp_prog_->setScaleY(1.5f);
	hp_prog_->setPercentage(100.0f);
	hp_prog_->setPosition(0.0f, 20.0f);
	this->addChild(hp_prog_, 1);

	this->setHP(100);
	this->setMaxHP(100);

	return true;
}

void DesertThug::update(float dt) {
	// nothing to do
}

void DesertThug::setState(MonsterState state) {
	image_->stopActionByTag(0);
	switch (state) {

	case WALK_LEFT: {
		this->image_->setFlippedX(true);
		auto animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_forward")));
		animationAct->setTag(0);
		image_->runAction(animationAct);
		break;
	}
	case WALK_RIGHT: {
		this->image_->setFlippedX(false);
		auto animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_forward")));
		animationAct->setTag(0);
		image_->runAction(animationAct);
		break;
	}
	case WALK_UP: {
		this->image_->setFlippedX(false);
		auto animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_up")));
		animationAct->setTag(0);
		image_->runAction(animationAct);
		break;
	}
	case WALK_DOWN: {
		this->image_->setFlippedX(false);
		auto animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_down")));
		animationAct->setTag(0);
		image_->runAction(animationAct);
		break;
	}
	case ATTACK_LEFT: {
		this->image_->setFlippedX(true);
		auto animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_attack")));
		animationAct->setTag(0);
		image_->runAction(animationAct);
		break;
	}
	case ATTACK_RIGHT: {
		this->image_->setFlippedX(false);
		auto animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_attack")));
		animationAct->setTag(0);
		image_->runAction(animationAct); 
		break;
	}
		case STAND: break;
		case DEAD: break;
		default: ;
	}
}

void DesertThug::keepGoing() {
	//static int current_point_ = 1; // there can't use static

	if (current_point_ < path_.size() && this->getPosition() != path_[current_point_]) {

		float dx = path_[current_point_].x * 1.08 - this->getPosition().x;
		float dy = path_[current_point_].y * 1.25 - this->getPosition().y;
		
		if (fabs(dy) > fabs(dx) && dy > 0) {
			// up
			setState(MonsterState::WALK_UP);
		} else if (fabs(dy) > fabs(dx) && dy < 0) {
			// down
			setState(MonsterState::WALK_DOWN);
		} else if (dx < 0) {
			// left
			setState(MonsterState::WALK_LEFT);
		} else {
			// right
			setState(MonsterState::WALK_RIGHT);
		}
		//this->runAction(Sequence::create(MoveTo::create(path_[i].distance(this->getPosition()) / 13.0f, path_[i]), CallFunc::create(CC_CALLBACK_0(DesertThug::keepGoing, this)), NULL));
		this->runAction(Sequence::create(MoveTo::create(0.3f, Vec2(path_[current_point_].x * 1.08, path_[current_point_].y * 1.25)), CallFunc::create(CC_CALLBACK_0(DesertThug::keepGoing, this)), NULL));
		++current_point_;
	}
}

#include "DesertThug.h"

DesertThug::DesertThug() {
}

DesertThug::~DesertThug() {
}

bool DesertThug::init(int type, const std::vector<Vec2> &path) {
	if (!Monster::init(type, path)) {
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
	this->image_->stopActionByTag(0);
	Action *animationAct;
	switch (state) {

	case WALK_LEFT: {
		this->image_->setFlippedX(true);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_forward")));
		break;
	}
	case WALK_RIGHT: {
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_forward")));
		break;
	}
	case WALK_UP: {
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_up")));
		break;
	}
	case WALK_DOWN: {
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_move_down")));
		break;
	}
	case ATTACK_LEFT: {
		this->image_->setFlippedX(true);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_attack")));
		break;
	}
	case ATTACK_RIGHT: {
		this->image_->setFlippedX(false);
		animationAct = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("desert_thug_attack")));
		break;
	}
		case STAND: ;
		default:
		{
			animationAct = nullptr;
		}
	}
	animationAct->setTag(0);
	image_->runAction(animationAct);
}

void DesertThug::keepGoing() {
	//static int current_target_point_ = 1; // there can't use static

	if (current_target_point_ < path_.size() && this->getPosition() != path_[current_target_point_]) {

		float dx = path_[current_target_point_].x - this->getPosition().x;
		float dy = path_[current_target_point_].y - this->getPosition().y;
		
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

		float distance = this->path_[current_target_point_].getDistance(this->path_[current_target_point_ - 1]);
		this->runAction(Sequence::create(MoveTo::create(distance / this->speed_, Vec2(path_[current_target_point_].x, path_[current_target_point_].y)), CallFunc::create(CC_CALLBACK_0(DesertThug::keepGoing, this)), NULL));
		++current_target_point_;
	}
}

void DesertThug::dying() {
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

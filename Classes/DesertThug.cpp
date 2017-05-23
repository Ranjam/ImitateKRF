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
	this->addChild(image_, 0);
	
	hp_bg_ = Sprite::createWithSpriteFrameName("lifebar_bg_small.png");
	hp_bg_->setPosition(0.0f, 20.0f);
	this->addChild(hp_bg_, 0);

	hp_prog_ = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_small.png"));
	hp_prog_->setType(ProgressTimer::Type::BAR);
	hp_prog_->setMidpoint(Vec2(0.0f, 0.5f));
	hp_prog_->setScaleY(2.0f);
	hp_prog_->setPercentage(100.0f);
	hp_prog_->setPosition(0.0f, 20.0f);
	this->addChild(hp_prog_, 1);

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
	static int i = 1;
	if (i < path_.size() && this->getPosition() != path_[i]) {

		float dx = path_[i].x * 1.15 - this->getPosition().x;
		float dy = path_[i].y * 1.3 - this->getPosition().y;
		
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
		this->runAction(Sequence::create(MoveTo::create(0.3f, Vec2(path_[i].x * 1.15, path_[i].y * 1.3)), CallFunc::create(CC_CALLBACK_0(DesertThug::keepGoing, this)), NULL));
		++i;
	}
}

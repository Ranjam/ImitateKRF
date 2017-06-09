#include "Monster.h"
#include "GameManager.h"

Monster::Monster() { }

Monster::~Monster() { }

bool Monster::init(int type, const std::vector<Vec2>& path, float speed, int hp, int max_hp, bool is_removed) {
	if (!Sprite::init()) {
		return false;
	}

	this->type_ = type;
	this->path_ = path;
	this->speed_ = speed;
	this->hp_ = hp;
	this->max_hp_ = max_hp;
	this->is_removed_ = is_removed;
	this->setPosition(path[0].x, path[0].y);

	return true;
}

void Monster::keepGoing() {
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
		this->runAction(Sequence::create(MoveTo::create(distance / this->speed_, Vec2(path_[current_target_point_].x, path_[current_target_point_].y)), CallFunc::create(CC_CALLBACK_0(Monster::keepGoing, this)), NULL));
		++current_target_point_;
	}
}

void Monster::getDamage(float damage) {
	this->hp_ -= damage;
	this->hp_prog_->setPercentage(static_cast<float>(this->hp_) / this->max_hp_ * 100);
	if (this->hp_ <= 0) {
		this->is_removed_ = true;
		GameManager::getInstance()->getMonsters().eraseObject(this);
		this->dying();
	}
}

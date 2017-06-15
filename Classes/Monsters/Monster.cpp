#include "Monster.h"
#include "Common/GameManager.h"

Monster::Monster() { }

Monster::~Monster() { }

bool Monster::init(int hp, int max_hp, float speed, float scope, bool is_removed, SpriteFrame *sprite_frame, HP_Type hp_type,
				   int type, const std::vector<Vec2>& path) {
	if (!Creature::init(hp, max_hp, speed, scope, is_removed, sprite_frame, hp_type)) {
		return false;
	}

	this->type_ = type;
	this->path_ = path;
	this->setPosition(path[0].x, path[0].y);

	return true;
}

void Monster::keepGoing() {
	//static int current_target_point_ = 1; // there can't use static

	if (current_target_point_ < path_.size() && this->getPosition() != path_[current_target_point_]) {

		auto relative = path_[current_target_point_] - this->getPosition();

		if (fabs(relative.y) > fabs(relative.x) && relative.y > 0) {
			// up
			setState(MonsterState::WALK_UP);
		} else if (fabs(relative.y) > fabs(relative.x) && relative.y < 0) {
			// down
			setState(MonsterState::WALK_DOWN);
		} else if (relative.x < 0) {
			// left
			setState(MonsterState::WALK_LEFT);
		} else {
			// right
			setState(MonsterState::WALK_RIGHT);
		}

		auto distance = this->path_[current_target_point_].getDistance(this->path_[current_target_point_ - 1]);
		this->runAction(Sequence::create(MoveTo::create(distance / this->speed_, Vec2(path_[current_target_point_].x, path_[current_target_point_].y)), 
										 CallFunc::create(CC_CALLBACK_0(Monster::keepGoing, this)),
										 NULL));
		++current_target_point_;
	}
}

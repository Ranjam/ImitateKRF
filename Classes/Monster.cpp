#include "Monster.h"
#include "GameManager.h"

Monster::Monster() { }

Monster::~Monster() { }

bool Monster::init(int type, const std::vector<Vec2> &path) {
	if (!Sprite::init()) {
		return false;
	}

	this->type_ = type;
	this->path_ = path;
	this->setPosition(path[0].x, path[0].y);
	this->is_dead_ = false;
	return true;
}

void Monster::getDamage(float damage) {
	this->hp_ -= damage;
	this->hp_prog_->setPercentage(static_cast<float>(this->hp_) / this->max_hp_ * 100);
	if (this->hp_ <= 0) {
		this->is_dead_ = true;
		GameManager::getInstance()->getMonsters().eraseObject(this);
		this->dying();
	}
}

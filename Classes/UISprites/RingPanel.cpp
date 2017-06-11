#include "RingPanel.h"


RingPanel::RingPanel() {
}


RingPanel::~RingPanel() {
}

bool RingPanel::init() {
	if (!Sprite::init()) {
		return false;
	}

	this->initWithSpriteFrameName("gui_ring.png");

	return true;
}

void RingPanel::show() {
	this->setVisible(true);
	this->runAction(ScaleTo::create(0.2f, 1.0f));
	is_shown_ = true;
}

void RingPanel::hide() {
	this->setVisible(false);
	this->runAction(ScaleTo::create(0.2f, 0.0f));
	is_shown_ = false;
}

void RingPanel::addIcon(BaseIcon *icon, float x, float y) {
	icons_.pushBack(icon);
	this->addChild(icon);
	icon->setPosition(x, y);
}

void RingPanel::clearIcons() {
	for (int i = 0; i < icons_.size(); ++i) {
		this->removeChild(icons_.at(i), true);
	}
	icons_.clear();
}

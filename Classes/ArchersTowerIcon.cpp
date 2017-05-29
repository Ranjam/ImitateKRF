#include "ArchersTowerIcon.h"
#include "Stronghold.h"


ArchersTowerIcon::ArchersTowerIcon() {
}


ArchersTowerIcon::~ArchersTowerIcon() {
}

bool ArchersTowerIcon::init() {
	if (!BaseIcon::init()) {
		return false;
	}

	this->image_ = Sprite::createWithSpriteFrameName("main_icons_0001.png");
	image_->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(image_, 1);
	return true;
}

void ArchersTowerIcon::onConfirmed() {
	confirm_->setVisible(false);
}

void ArchersTowerIcon::onClicked() {
	confirm_->setVisible(true);
}

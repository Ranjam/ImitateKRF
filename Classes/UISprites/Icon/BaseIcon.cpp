#include "BaseIcon.h"
#include "../RingPanel.h"
#include "Common/SoundManager.h"
#include "Common/Resources.h"


BaseIcon::BaseIcon() {
}


BaseIcon::~BaseIcon() {
}

bool BaseIcon::init() {
	if (!Sprite::init()) {
		return false;
	}

	// background icon
	this->initWithSpriteFrameName("main_icons_0014.png");

	// confirm image
	confirm_ = Sprite::createWithSpriteFrameName("main_icons_0019.png");
	confirm_->setAnchorPoint(Vec2(0.0f, 0.0f));
	confirm_->setVisible(false);
	this->addChild(confirm_, 3);

	// click listener
	auto click_listener = EventListenerTouchOneByOne::create();
	click_listener->setSwallowTouches(true);

	click_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (this->getBoundingBox().containsPoint(this->getParent()->convertTouchToNodeSpace(touch))) {
			SoundManager::getInstance()->playEffect(s_effect_open_tower);
			return true;
		} else {
			onCanceled();
			confirm_->setVisible(false);
			selected_ = false;
		}
		return false;
	};

	click_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		if (!selected_) {
			// on clicked
			onClicked();
			confirm_->setVisible(true);
		} else {
			// confirmed
			onConfirmed();
			confirm_->setVisible(false);
			this->_eventDispatcher->pauseEventListenersForTarget(this, true);
		}
		selected_ = !selected_;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(click_listener, this);

	return true;
}
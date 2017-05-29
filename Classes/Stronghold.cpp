#include "Stronghold.h"
#include "ArchersTowerIcon.h"


Stronghold::Stronghold() {
}


Stronghold::~Stronghold() {
}

bool Stronghold::init() {
	if (!Sprite::init()) {
		return false;
	}
	// terrain
	auto sprite = Sprite::createWithSpriteFrameName("build_terrain_0004.png");
	this->addChild(sprite);

	// ring panel
	ring_panel_ = RingPanel::create();
	this->addChild(ring_panel_);
	ring_panel_->setScale(0.0f);
	ring_panel_->hide();

	ring_panel_->addIcon(ArchersTowerIcon::create(), ring_panel_->getContentSize().width / 2, ring_panel_->getContentSize().height);
	ring_panel_->addIcon(BaseIcon::create(), ring_panel_->getContentSize().width / 2, 0);
	ring_panel_->addIcon(BaseIcon::create(), 0.0f, ring_panel_->getContentSize().height / 2);
	ring_panel_->addIcon(BaseIcon::create(), ring_panel_->getContentSize().width, ring_panel_->getContentSize().height / 2);

	// terrain click
	auto click_listener = EventListenerTouchOneByOne::create();
	click_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (sprite->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {

			return true;
		} else {
			ring_panel_->hide();
		}
		return false;
	};
	click_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		if (ring_panel_->isShow()) {
			ring_panel_->hide();
		} else {
			ring_panel_->show();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(click_listener, sprite);

	return true;
}

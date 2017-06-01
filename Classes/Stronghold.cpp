#include "Stronghold.h"
#include "ArchersTowerIcon.h"
#include "ArchersTower.h"


Stronghold::Stronghold() {
}


Stronghold::~Stronghold() {
}

bool Stronghold::init() {
	if (!Sprite::init()) {
		return false;
	}
	// terrain
	image_ = Sprite::createWithSpriteFrameName("build_terrain_0004.png");
	this->addChild(image_, -1);
	
	// ring panel
	ring_panel_ = RingPanel::create();
	this->addChild(ring_panel_);
	ring_panel_->setScale(0.0f);
	ring_panel_->hide();

	// adjust the position
	float t = sqrt(2.0f) / 4.0f;
	float p = 1.0f / 2;
	ring_panel_->addIcon(ArchersTowerIcon::create(), (p - t) * ring_panel_->getContentSize().width, (p + t) * ring_panel_->getContentSize().height);
	ring_panel_->addIcon(BaseIcon::create(), (p + t) * ring_panel_->getContentSize().width, (p + t) * ring_panel_->getContentSize().height);
	ring_panel_->addIcon(BaseIcon::create(), (p - t) * ring_panel_->getContentSize().width, (p - t) * ring_panel_->getContentSize().height);
	ring_panel_->addIcon(BaseIcon::create(), (p + t) * ring_panel_->getContentSize().width, (p - t) * ring_panel_->getContentSize().height);

	// terrain click
	auto click_listener = EventListenerTouchOneByOne::create();
	click_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (image_->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			return true;
		} else {
			ring_panel_->hide();
			this->hidePreview();
		}
		return false;
	};
	click_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		if (ring_panel_->isShow()) {
			ring_panel_->hide();
			this->hidePreview();
		} else {
			ring_panel_->show();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(click_listener, image_);

	return true;
}

void Stronghold::showPreview(BaseTower::TowerType tower_type) {
	// hide last preview
	hidePreview();

	// add preview
	switch (tower_type) {
		case BaseTower::ARCHER:
			preview_ = Sprite::createWithSpriteFrameName("tower_preview_archer.png");
			break;
		case BaseTower::MILITIA:
			preview_ = Sprite::createWithSpriteFrameName("tower_preview_barrack.png");
			break;
		case BaseTower::MAGE: 
			preview_ = Sprite::createWithSpriteFrameName("tower_preview_mage.png");
			break;
		case BaseTower::BOMBARD: 
			preview_ = Sprite::createWithSpriteFrameName("tower_preview_artillery.png");
			break;
		default: ;
	}
	if (preview_ != nullptr) {
		preview_->setPosition(0.0f, 25.0f);
		this->addChild(preview_, 1);
	}
}

void Stronghold::hidePreview() {
	if (preview_ != nullptr) {
		this->removeChild(preview_, true);
	}
}

void Stronghold::buildTower(BaseTower::TowerType tower_type) {
	switch (tower_type) {
		case BaseTower::ARCHER:
			tower_ = ArchersTower::create();
			break;
		case BaseTower::MILITIA: break;
		case BaseTower::MAGE: break;
		case BaseTower::BOMBARD: break;
		case BaseTower::UNDEFINED: break;
		default: ;
	}
	if (tower_ != nullptr) {
		this->addChild(tower_);
		tower_->setPosition(0.0f, 25.0f);

		// pause the event listener
		_eventDispatcher->pauseEventListenersForTarget(image_);
	}
}

void Stronghold::removeTower() {
	this->removeChild(tower_, true);
	tower_ = nullptr;

	// resume the event listener
	_eventDispatcher->resumeEventListenersForTarget(image_);
}

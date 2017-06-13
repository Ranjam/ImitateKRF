#include "Stronghold.h"
#include "Towers/ArchersTower.h"
#include "Towers/BarrackTower.h"

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
	this->addChild(image_, Zorder::BACKGROUND);
	
	// ring panel
	ring_panel_ = RingPanel::create();
	this->addChild(ring_panel_, Zorder::RING_PANEL);
	ring_panel_->setScale(0.0f);
	ring_panel_->hide();

	// adjust the position
	float t = sqrt(2.0f) / 4.0f;
	float p = 1.0f / 2;
	ring_panel_->addIcon(BaseIcon::create(BaseIcon::IconType::ARCHERS_TOWER), (p - t) * ring_panel_->getContentSize().width, (p + t) * ring_panel_->getContentSize().height);
	ring_panel_->addIcon(BaseIcon::create(BaseIcon::IconType::BARRACK_TOWER), (p + t) * ring_panel_->getContentSize().width, (p + t) * ring_panel_->getContentSize().height);
	ring_panel_->addIcon(BaseIcon::create(BaseIcon::IconType::NONE), (p - t) * ring_panel_->getContentSize().width, (p - t) * ring_panel_->getContentSize().height);
	ring_panel_->addIcon(BaseIcon::create(BaseIcon::IconType::NONE), (p + t) * ring_panel_->getContentSize().width, (p - t) * ring_panel_->getContentSize().height);

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
	// add preview
	switch (tower_type) {
		case BaseTower::ARCHER:
			preview_ = Sprite::createWithSpriteFrameName("tower_preview_archer.png");
			addRangeCircle(RangeCircle::RANGE, ArchersTower::kArcherTowerLv1Scope);
			break;
		case BaseTower::BARRACK:
			preview_ = Sprite::createWithSpriteFrameName("tower_preview_barrack.png");
			addRangeCircle(RangeCircle::RALLY, BarrackTower::kBarrackTowerLv1Scope);
			break;
		case BaseTower::MAGE: 
			preview_ = Sprite::createWithSpriteFrameName("tower_preview_mage.png");
			break;
		case BaseTower::ARTILLERY: 
			preview_ = Sprite::createWithSpriteFrameName("tower_preview_artillery.png");
			break;
		case BaseTower::UNDEFINED: break;
	}
	if (preview_ != nullptr) {
		preview_->setPosition(0.0f, 25.0f);
		this->addChild(preview_, Zorder::TOWER);
	}
}

void Stronghold::hidePreview() {
	if (preview_ != nullptr) {
		this->removeChild(preview_, true);
	}
	removeRangeCircle();
}

void Stronghold::buildTower(BaseTower::TowerType tower_type) {
	switch (tower_type) {
		case BaseTower::ARCHER:
			tower_ = ArchersTower::create();
			break;
		case BaseTower::BARRACK: 
			tower_ = BarrackTower::create();
			break;
		case BaseTower::MAGE: break;
		case BaseTower::ARTILLERY: break;
		case BaseTower::UNDEFINED: break;
		default: ;
	}
	if (tower_ != nullptr) {
		this->addChild(tower_, Zorder::TOWER);
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

void Stronghold::addRangeCircle(RangeCircle::RangeType type, float scope) {
	if (!range_circle_added_) {
		this->addChild(RangeCircle::create(type, scope), Zorder::RANGE_CIRCLE, 999);
		range_circle_added_ = true;
	}
}

void Stronghold::removeRangeCircle() {
	if (range_circle_added_) {
		this->removeChildByTag(999, true);
		range_circle_added_ = false;
	}
}

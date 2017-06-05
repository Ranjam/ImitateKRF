#include "ArchersTowerIcon.h"
#include "Stronghold.h"
#include "ArchersTower.h"
#include "RangeCircle.h"


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
	static_cast<RingPanel *>(this->getParent())->hide();
	static_cast<Stronghold *>(this->getParent()->getParent())->hidePreview();
	static_cast<Stronghold *>(this->getParent()->getParent())->buildTower(BaseTower::TowerType::ARCHER);
	static_cast<Stronghold *>(this->getParent()->getParent())->removeChildByTag(999, true);
}

void ArchersTowerIcon::onClicked() {
	static_cast<Stronghold *>(this->getParent()->getParent())->showPreview(BaseTower::ARCHER);
	static_cast<Stronghold *>(this->getParent()->getParent())->addChild(RangeCircle::create(RangeCircle::RANGE, ArchersTower::kArcherTowerLv1Scope), -1, 999);
}

void ArchersTowerIcon::onCanceled() {
	static_cast<Stronghold *>(this->getParent()->getParent())->removeChildByTag(999, true);
}

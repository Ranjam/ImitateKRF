#include "ArchersTowerIcon.h"
#include "Towers/ArchersTower.h"
#include "UISprites/RangeCircle.h"
#include "UISprites/RingPanel.h"
#include "UISprites/Stronghold.h"


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
	static_cast<Stronghold *>(this->getParent()->getParent())->removeRangeCircle();
}

void ArchersTowerIcon::onClicked() {
	static_cast<Stronghold *>(this->getParent()->getParent())->showPreview(BaseTower::ARCHER);
	static_cast<Stronghold *>(this->getParent()->getParent())->addRangeCircle(RangeCircle::RANGE, ArchersTower::kArcherTowerLv1Scope);
}

void ArchersTowerIcon::onCanceled() {
	static_cast<Stronghold *>(this->getParent()->getParent())->removeRangeCircle();
}

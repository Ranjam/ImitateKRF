#include "BaseIcon.h"
#include "RingPanel.h"
#include "Common/SoundManager.h"
#include "Common/Resources.h"
#include "UISprites/Stronghold.h"
#include "Towers/ArchersTower.h"


BaseIcon::BaseIcon() {
}


BaseIcon::~BaseIcon() {
}

bool BaseIcon::init(IconType type) {
	if (!Sprite::init()) {
		return false;
	}

	this->icon_type_ = type;

	// foreground
	switch (icon_type_) {
		case ARCHERS_TOWER: 
			this->image_ = Sprite::createWithSpriteFrameName("main_icons_0001.png");
			break;
		case BARRACK_TOWER:
			this->image_ = Sprite::createWithSpriteFrameName("main_icons_0002.png");
			break;
		case MAGE_TOWER: 
			this->image_ = Sprite::createWithSpriteFrameName("main_icons_0003.png");
			break;
		case ARTILLERY_TOWER: 
			this->image_ = Sprite::createWithSpriteFrameName("main_icons_0004.png");
			break;
		case NONE: 
			this->image_ = Sprite::createWithSpriteFrameName("main_icons_0014.png");
			break;
	}
	this->addChild(image_, Zorder::FOREGROUND);

	// background icon
	this->background = Sprite::createWithSpriteFrameName("main_icons_0014.png");
	this->addChild(background, Zorder::BACKGROUND);

	// confirm image
	confirm_ = Sprite::createWithSpriteFrameName("main_icons_0019.png");
	confirm_->setVisible(false);
	this->addChild(confirm_, Zorder::CONFIRM);

	// click listener
	auto click_listener = EventListenerTouchOneByOne::create();
	click_listener->setSwallowTouches(true);

	click_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (this->image_->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			SoundManager::getInstance()->playEffect(s_effect_open_tower);
			return true;
		} else {
			onCanceled();
		}
		return false;
	};

	click_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		if (!selected_) {
			// on clicked
			onClicked();
		} else {
			// confirmed
			onConfirmed();
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(click_listener, image_);

	return true;
}

void BaseIcon::onClicked() {
	static_cast<RingPanel *>(this->getParent())->cancelAllIconClick();
	confirm_->setVisible(true);
	selected_ = true;
	switch (icon_type_) {
		case ARCHERS_TOWER: 
			static_cast<Stronghold *>(this->getParent()->getParent())->showPreview(BaseTower::TowerType::ARCHER);
			break;
		case BARRACK_TOWER: 
			static_cast<Stronghold *>(this->getParent()->getParent())->showPreview(BaseTower::TowerType::BARRACK);
			break;
		case MAGE_TOWER: 
			static_cast<Stronghold *>(this->getParent()->getParent())->showPreview(BaseTower::TowerType::MAGE);
			break;
		case ARTILLERY_TOWER: 
			static_cast<Stronghold *>(this->getParent()->getParent())->showPreview(BaseTower::TowerType::ARTILLERY);
			break;
		case NONE: break;
	}
}

void BaseIcon::onCanceled() {
	confirm_->setVisible(false);
	selected_ = false;
	static_cast<Stronghold *>(this->getParent()->getParent())->hidePreview();
}

void BaseIcon::onConfirmed() {
	confirm_->setVisible(false);
	selected_ = false;
	static_cast<RingPanel *>(this->getParent())->hide();
	static_cast<Stronghold *>(this->getParent()->getParent())->hidePreview();

	switch (icon_type_) {
		case ARCHERS_TOWER: 
			static_cast<Stronghold *>(this->getParent()->getParent())->buildTower(BaseTower::TowerType::ARCHER);
			break;
		case BARRACK_TOWER: 
			static_cast<Stronghold *>(this->getParent()->getParent())->buildTower(BaseTower::TowerType::BARRACK);
			break;
		case MAGE_TOWER: 
			static_cast<Stronghold *>(this->getParent()->getParent())->buildTower(BaseTower::TowerType::MAGE);
			break;
		case ARTILLERY_TOWER: 
			static_cast<Stronghold *>(this->getParent()->getParent())->buildTower(BaseTower::TowerType::ARTILLERY);
			break;
		case NONE: break;
	}
}

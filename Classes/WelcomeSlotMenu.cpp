#include "WelcomeSlotMenu.h"
#include "Common.h"


WelcomeSlotMenu::WelcomeSlotMenu() {
}


WelcomeSlotMenu::~WelcomeSlotMenu() {
}

bool WelcomeSlotMenu::init() {
	if (!Sprite::init()) {
		return false;
	}
	
	// background menu
	auto sprite_background = Sprite::createWithSpriteFrameName("mainmenu_saveslot_bg.png");
	sprite_background->setPosition(winSize.width / 2, winSize.height / 2 - sprite_background->getContentSize().height / 3);
	sprite_background->setTag(BACKGROUND);
	this->addChild(sprite_background, -1);
	
	// assume all have data
	UserDefault::getInstance()->setBoolForKey("save01", true);
	UserDefault::getInstance()->setBoolForKey("save02", true);
	UserDefault::getInstance()->setBoolForKey("save03", true);

	// slot 01
	auto sprite_slot01 = Sprite::createWithSpriteFrameName("mainmenu_saveslot_0001.png");
	sprite_slot01->setPosition(winSize.width / 2 - sprite_slot01->getContentSize().width - 15.0f, 
							   winSize.height / 2 - sprite_background->getContentSize().height / 3);
	sprite_slot01->setTag(SLOT01);
	this->addChild(sprite_slot01, 1);
	setSlotDisplay(SLOT01, "save01");
	bindEventOneByOne(SLOT01);

	// slot 02
	auto sprite_slot02 = Sprite::createWithSpriteFrameName("mainmenu_saveslot_0001.png");
	sprite_slot02->setPosition(winSize.width / 2, winSize.height / 2 - sprite_background->getContentSize().height / 3);
	sprite_slot02->setTag(SLOT02);
	this->addChild(sprite_slot02, 1);
	setSlotDisplay(SLOT02, "save02");
	bindEventOneByOne(SLOT02);

	// slot 03
	auto sprite_slot03 = Sprite::createWithSpriteFrameName("mainmenu_saveslot_0001.png");
	sprite_slot03->setPosition(winSize.width / 2 + sprite_slot03->getContentSize().width + 15.0f, 
							   winSize.height / 2 - sprite_background->getContentSize().height / 3);
	sprite_slot03->setTag(SLOT03);
	this->addChild(sprite_slot03, 1);
	setSlotDisplay(SLOT03, "save03");
	bindEventOneByOne(SLOT03);

	return true;
}

void WelcomeSlotMenu::setSlotDisplay(Tag slot_tag, const char *save_name) {
	if (UserDefault::getInstance()->getBoolForKey(save_name)) {
		showSaveData(slot_tag);
	} else {
		showNewGame(slot_tag);
	}
}

void WelcomeSlotMenu::showNewGame(Tag slot_tag) {
	auto sprite_slot = this->getChildByTag(slot_tag);
	auto sprite_background = this->getChildByTag(BACKGROUND);
	auto new_game = Label::createWithTTF("New Game", "fonts/Comic_Book.ttf", 35);
	new_game->setPosition(winSize.width / 2 + (sprite_slot->getContentSize().width + 15.0f) * (slot_tag - 2),
						  winSize.height / 2 - sprite_background->getContentSize().height / 3);
	this->addChild(new_game, 2);
}

void WelcomeSlotMenu::showSaveData(Tag slot_tag) {
	auto sprite_slot = this->getChildByTag(slot_tag);
	auto sprite_background = this->getChildByTag(BACKGROUND);
	// SLOT 02
	auto save_hint = Label::createWithTTF(StringUtils::format("SLOT 0%d", slot_tag), "fonts/Comic_Book.ttf", 25);
	save_hint->setPosition(winSize.width / 2 + (sprite_slot->getContentSize().width + 15.0f) * (slot_tag - 2),
						   winSize.height / 2 - sprite_background->getContentSize().height / 3 + 15.0f);
	save_hint->setName(StringUtils::format("hint_%d", slot_tag));
	this->addChild(save_hint, 2);

	// icon
	auto icon = Sprite::createWithSpriteFrameName("mainmenu_saveslot_icons_0001.png");
	icon->setPosition(winSize.width / 2 + (sprite_slot->getContentSize().width + 15.0f) * (slot_tag - 2) - 50.0f,
					  winSize.height / 2 - sprite_background->getContentSize().height / 3 - 15.0f);
	icon->setName(StringUtils::format("icon_%d", slot_tag));
	this->addChild(icon, 2);

	// 0/105
	auto info = Label::createWithTTF("0/105", "fonts/Comic_Book.ttf", 25);
	info->setPosition(winSize.width / 2 + (sprite_slot->getContentSize().width + 15.0f) * (slot_tag - 2) + 30.0f,
					  winSize.height / 2 - sprite_background->getContentSize().height / 3 - 15.0f);
	info->setName(StringUtils::format("info_%d", slot_tag));
	this->addChild(info, 2);

	// delete save
	auto button_delete = Sprite::createWithSpriteFrameName("mainmenu_saveslot_delete_0001.png");
	button_delete->setPosition(sprite_slot->getPosition().x + sprite_slot->getContentSize().width / 2 - 20.0f,
							   sprite_slot->getPosition().y + sprite_slot->getContentSize().height / 2 - 20.0f);
	button_delete->setName(StringUtils::format("delete_%d", slot_tag));
	this->addChild(button_delete, 2);

	bindDeleteEvent(slot_tag);
}

void WelcomeSlotMenu::showSelect(Tag slot_tag) {
	auto sprite_slot = this->getChildByTag(slot_tag);

	auto hint = this->getChildByName(StringUtils::format("hint_%d", slot_tag));
	auto icon = this->getChildByName(StringUtils::format("icon_%d", slot_tag));
	auto info = this->getChildByName(StringUtils::format("info_%d", slot_tag));
	this->removeChild(hint, true);
	this->removeChild(icon, true);
	this->removeChild(info, true);
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(sprite_slot);
	
	// confirm
	auto select_yes = Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0001.png");
	select_yes->setPosition(sprite_slot->getPosition().x - 50.0f,
							sprite_slot->getPosition().y);
	this->addChild(select_yes, 2);

	// no
	auto select_no = Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0002.png");
	select_no->setPosition(sprite_slot->getPosition().x + 50.0f,
						   sprite_slot->getPosition().y);
	this->addChild(select_no, 2);

	// yes listener
	auto yes_listener = EventListenerTouchOneByOne::create();
	yes_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		auto target = static_cast<Sprite *>(event->getCurrentTarget());
		if (target->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			target->setScale(1.2f);
			return true;
		}
		return false;
	};
	yes_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		auto target = static_cast<Sprite *>(event->getCurrentTarget());
		if (target->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			target->setScale(1.0f);
			this->removeChild(select_no, true);
			this->removeChild(target, true);
			Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(sprite_slot);
			showNewGame(slot_tag);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(yes_listener, select_yes);

	// no listener
	auto no_listener = EventListenerTouchOneByOne::create();
	no_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		auto target = static_cast<Sprite *>(event->getCurrentTarget());
		if (target->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			target->setScale(1.2f);
			return true;
		}
		return false;
	};
	no_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		auto target = static_cast<Sprite *>(event->getCurrentTarget());
		if (target->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			target->setScale(1.0f);
			this->removeChild(select_yes, true);
			this->removeChild(target, true);
			Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(sprite_slot);
			showSaveData(slot_tag);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(no_listener, select_no);
}

void WelcomeSlotMenu::bindEventOneByOne(Tag slot_tag) {
	auto sprite_slot = static_cast<Sprite *>(this->getChildByTag(slot_tag));
	auto slot_listener = EventListenerTouchOneByOne::create();
	slot_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (sprite_slot->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			sprite_slot->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_0002.png"));
			return true;
		}
		return false;
	};
	// Enter game
	slot_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		sprite_slot->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_0001.png"));
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(slot_listener, sprite_slot);
}

void WelcomeSlotMenu::bindDeleteEvent(Tag slot_tag) {
	auto button_delete = static_cast<Sprite *>(this->getChildByName(StringUtils::format("delete_%d", slot_tag)));
	auto button_delete_listener = EventListenerTouchOneByOne::create();
	button_delete_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (button_delete->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			button_delete->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_delete_0002.png"));
			return true;
		}
		return false;
	};
	button_delete_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		button_delete->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_delete_0001.png"));
		showSelect(slot_tag);
		this->removeChild(button_delete, true);
	};

	button_delete_listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(button_delete_listener, button_delete);
}

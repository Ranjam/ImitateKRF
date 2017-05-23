#include "WelcomeScene.h"
#include "Common.h"
#include "WelcomeSlotMenu.h"

USING_NS_CC;

Scene* WelcomeScene::createScene() {
    auto scene = Scene::create();
    
    auto layer = WelcomeScene::create();

    scene->addChild(layer);

    return scene;
}

bool WelcomeScene::init() {
	if (!Layer::init()) {
		return false;
	}

	// Add background
	auto sprite_background = Sprite::createWithSpriteFrameName("mainmenu_bg.png");
	sprite_background->setPosition(Vec2(winSize.width / 2.0f, winSize.height / 2.0f));
	this->addChild(sprite_background, -1);

	// Add logo and logo animation
	auto sprite_logo = Sprite::createWithSpriteFrameName("logo.png");
	sprite_logo->setPosition(winSize.width / 2.0f, winSize.height - sprite_logo->getContentSize().height / 2.0f);
	sprite_logo->setScale(0.2f);
	this->addChild(sprite_logo, 1);
	auto sequence = Sequence::create(ScaleTo::create(0.3f, 1.5f), ScaleTo::create(0.2f, 1.0f), NULL);
	sprite_logo->runAction(sequence);
	// start button
	scheduleOnce(schedule_selector(WelcomeScene::startButtonAnimationCallback), 0.5f);
	
	// logo animation
	scheduleOnce(schedule_selector(WelcomeScene::logoAnimationCallback), 0.5f);

	auto slot_menu = WelcomeSlotMenu::create();
	slot_menu->setPosition(0, -winSize.height);
	this->addChild(slot_menu);
	slot_menu->setTag(Tag::SLOT_MENU);
	
	// close menu button
	auto button_close = Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0001.png");
	button_close->setPosition(winSize.width / 2.0f, 100.0f - winSize.height);
	button_close->setTag(Tag::CLOSE_BUTTON);
	this->addChild(button_close);
	
	auto button_close_listener = EventListenerTouchOneByOne::create();
	button_close_listener->onTouchBegan = [&](Touch *touch, Event *event)->bool {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		if (target->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_close_0002.png"));
			return true;
		}
		return false;
	};
	button_close_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		if (target->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_close_0001.png"));
			auto start_button = this->getChildByTag(Tag::START_BUTTON);
			slot_menu->runAction(MoveBy::create(0.3f, Vec2(0.0f, -winSize.height)));
			target->runAction(MoveBy::create(0.3f, Vec2(0.0f, -winSize.height)));
			start_button->setVisible(true);
			start_button->runAction(MoveBy::create(0.5f, Vec2(0.0f, -200.0f)));
			Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(start_button);
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(button_close_listener, button_close);

	return true;
}

void WelcomeScene::logoAnimationCallback(float dt) {
	SpriteFrame *frame;
	Vector<SpriteFrame *> sprite_frames;
	for (int i = 1; i < 27; ++i) {
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("logo_brillo_00%02d.png", i));
		if (frame != nullptr) {
			sprite_frames.pushBack(frame);
		}
	}
	auto animation = Animation::createWithSpriteFrames(sprite_frames, 0.1f);
	auto sprite_logo_brillo = Sprite::createWithSpriteFrameName("logo_brillo_0001.png");
	sprite_logo_brillo->setPosition(winSize.width / 2.0f, winSize.height - sprite_logo_brillo->getContentSize().height / 2.0f);
	this->addChild(sprite_logo_brillo, 2);
	sprite_logo_brillo->runAction(RepeatForever::create(Animate::create(animation)));
}

void WelcomeScene::startButtonAnimationCallback(float dt) {
	// Start button
	auto button_start = Sprite::createWithSpriteFrameName("menu_startchain_0001.png");
	button_start->setPosition(winSize.width / 2.0f, winSize.height / 2.0f + button_start->getContentSize().height / 2.0f);
	button_start->setTag(Tag::START_BUTTON);
	this->addChild(button_start, 0);
	button_start->runAction(MoveTo::create(1.0f, Vec2(winSize.width / 2.0f, winSize.height / 2.0f - button_start->getContentSize().height / 6.0f)));

	// button event
	auto button_start_event_listener = EventListenerTouchOneByOne::create();

	button_start_event_listener->onTouchBegan = [](Touch *touch, Event *event)->bool {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertTouchToNodeSpace(touch);
		Size size = target->getContentSize();
		Rect rect = Rect(0 + 40, 0 + 30, size.width - 80, size.height / 3 + 15);
		if (rect.containsPoint(locationInNode)) {
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0002.png"));
			return true;
		}
		return false;
	};

	// on clicked start button
	button_start_event_listener->onTouchEnded = [&](Touch *touch, Event *event)->void {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertTouchToNodeSpace(touch);
		Size size = target->getContentSize();
		Rect rect = Rect(0 + 40, 0 + 30, size.width - 80, size.height / 3 + 15);
		if (rect.containsPoint(locationInNode)) {
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0001.png"));
			target->runAction(MoveBy::create(0.3f, Vec2(0.0f, 200.0f)));
			target->setVisible(false);
			Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(target);
			setSaveSlotMenu();
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(button_start_event_listener, button_start);
}

void WelcomeScene::setSaveSlotMenu() {
	auto slot_menu = this->getChildByTag(Tag::SLOT_MENU);
	slot_menu->runAction(MoveBy::create(0.3f, Vec2(0.0f, winSize.height)));
	auto button_close = this->getChildByTag(Tag::CLOSE_BUTTON);
	button_close->runAction(MoveBy::create(0.3f, Vec2(0.0f, winSize.height)));
}

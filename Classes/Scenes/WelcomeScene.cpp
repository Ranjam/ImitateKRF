#include "WelcomeScene.h"
#include "Common/CommonMacro.h"
#include "UI/WelcomeSlotMenu.h"
#include "Common/SoundManager.h"
#include "Common/Resources.h"
#include "CreditsScene.h"

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

	// add background
	auto bg = Sprite::createWithSpriteFrameName("mainmenu_bg.png");
	bg->setPosition(Vec2(winSize.width / 2.0f, winSize.height / 2.0f));
	bg->setScaleY(1.1f);
	this->addChild(bg, Zorder::BACKGROUND);

	// add logo and logo animation
	auto logo = Sprite::createWithSpriteFrameName("logo.png");
	logo->setPosition(winSize.width / 2.0f, winSize.height - logo->getContentSize().height / 2.0f);
	logo->setScale(0.2f);
	this->addChild(logo, Zorder::SIMPLE_UI);
	logo->runAction(Sequence::create(ScaleTo::create(0.3f, 1.5f), ScaleTo::create(0.2f, 1.0f), NULL));

	// start button
	scheduleOnce(schedule_selector(WelcomeScene::startButtonAnimationCallback), 0.5f);

	// logo animation
	scheduleOnce(schedule_selector(WelcomeScene::logoAnimationCallback), 0.5f);

	auto slot_menu = WelcomeSlotMenu::create();
	slot_menu->setPosition(0, -winSize.height);
	this->addChild(slot_menu, Zorder::SIMPLE_UI);
	slot_menu->setTag(Tag::SLOT_MENU);
	
	// close menu button
	auto button_close = Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0001.png");
	button_close->setPosition(winSize.width / 2.0f, 100.0f - winSize.height);
	button_close->setTag(Tag::CLOSE_BUTTON);
	this->addChild(button_close, Zorder::SIMPLE_UI);
	
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

			// play effect
			SoundManager::getInstance()->playEffect(s_effect_button_click);

			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_close_0001.png"));
			slot_menu->runAction(MoveBy::create(0.3f, Vec2(0.0f, -winSize.height)));
			target->runAction(MoveBy::create(0.3f, Vec2(0.0f, -winSize.height)));
			startButtonAnimationCallback(0.16f);
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(button_close_listener, button_close);

	SoundManager::getInstance()->playMusic(s_music_welcome);

	return true;
}

void WelcomeScene::logoAnimationCallback(float dt) {
	auto sprite_logo_brillo = Sprite::createWithSpriteFrameName("logo_brillo_0001.png");
	sprite_logo_brillo->setPosition(winSize.width / 2.0f, winSize.height - sprite_logo_brillo->getContentSize().height / 2.0f);
	this->addChild(sprite_logo_brillo, Zorder::LOGO);
	sprite_logo_brillo->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("logo_animation"))));
}

void WelcomeScene::startButtonAnimationCallback(float dt) {
	// Start button
	auto button_start = Sprite::createWithSpriteFrameName("menu_startchain_0001.png");
	button_start->setPosition(winSize.width / 2.0f - 5.0f, winSize.height / 2.0f + button_start->getContentSize().height / 2.0f);
	button_start->setTag(Tag::START_BUTTON);
	this->addChild(button_start, Zorder::START);
	button_start->runAction(Sequence::create(MoveTo::create(0.8f, Vec2(winSize.width / 2.0f - 5.0f, winSize.height / 2.0f - button_start->getContentSize().height / 6.0f)),
											 CallFunc::create(CC_CALLBACK_0(WelcomeScene::creditsButtonAnimationCallback, this)),
											 NULL));

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

		SoundManager::getInstance()->playEffect(s_effect_button_click);

		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertTouchToNodeSpace(touch);
		Size size = target->getContentSize();
		Rect rect = Rect(0 + 40, 0 + 30, size.width - 80, size.height / 3 + 15);
		if (rect.containsPoint(locationInNode)) {
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0001.png"));
			target->runAction(MoveBy::create(0.3f, Vec2(0.0f, 200.0f)));
			target->setVisible(false);
			this->_eventDispatcher->pauseEventListenersForTarget(target);
			this->removeChildByTag(Tag::START_BUTTON);
			this->removeChildByTag(Tag::CREDITS_BUTTON);
			setSaveSlotMenu();
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(button_start_event_listener, button_start);
}

void WelcomeScene::creditsButtonAnimationCallback() {
	auto start_button = this->getChildByTag(Tag::START_BUTTON);
	// credits button
	auto button_credits = Sprite::createWithSpriteFrameName("menu_creditschain_0001.png");
	button_credits->setPosition(start_button->getPosition().x - 5.0f, start_button->getPosition().y - 80);
	button_credits->setTag(Tag::CREDITS_BUTTON);
	this->addChild(button_credits, Zorder::CREDITS);
	button_credits->runAction(MoveTo::create(0.5f, Vec2(start_button->getPosition().x - 5.0f, start_button->getPosition().y - button_credits->getContentSize().height)));

	// button event
	auto credits_listener = EventListenerTouchOneByOne::create();

	credits_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (button_credits->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			button_credits->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_creditschain_0002.png"));
			return true;
		}
		return false;
	};

	// on clicked start button
	credits_listener->onTouchEnded = [=](Touch *touch, Event *event)->void {

		SoundManager::getInstance()->playEffect(s_effect_button_click);
		button_credits->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_creditschain_0001.png"));

		auto credit_scene = CreditsScene::createScene();
		Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5f, credit_scene));
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(credits_listener, button_credits);
}

void WelcomeScene::setSaveSlotMenu() {
	auto slot_menu = this->getChildByTag(Tag::SLOT_MENU);
	slot_menu->runAction(MoveBy::create(0.3f, Vec2(0.0f, winSize.height)));
	auto button_close = this->getChildByTag(Tag::CLOSE_BUTTON);
	button_close->runAction(MoveBy::create(0.3f, Vec2(0.0f, winSize.height)));
}

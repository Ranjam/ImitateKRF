#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "Common.h"

USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = WelcomeScene::create();

    scene->addChild(layer);

    return scene;
}

bool WelcomeScene::init() {
	if (!Layer::init()) {
		return false;
	}

	// Load sprite frame
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_1-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainmenu_spritesheet_32_2-hd.plist");

	// Add background
	auto sprite_background = Sprite::createWithSpriteFrameName("mainmenu_bg.png");
	sprite_background->setPosition(Vec2(winSize.width / 2.0f, winSize.height / 2.0f));
	this->addChild(sprite_background, -1);

	// Add logo and logo animation
	auto sprite_logo = Sprite::createWithSpriteFrameName("logo.png");
	sprite_logo->setPosition(winSize.width / 2.0f, winSize.height - sprite_logo->getContentSize().height / 2.0f);
	sprite_logo->setScale(0.2);
	this->addChild(sprite_logo, 1);
	auto sequence = Sequence::create(ScaleTo::create(0.3f, 1.5f), ScaleTo::create(0.2f, 1.0f), NULL);
	sprite_logo->runAction(sequence);
	// start button
	scheduleOnce(schedule_selector(WelcomeScene::startButtonAnimationCallback), 0.5f);
	
	// logo animation
	scheduleOnce(schedule_selector(WelcomeScene::logoAnimationCallback), 0.5f);

	return true;
}

void WelcomeScene::logoAnimationCallback(float dt) {
	SpriteFrame *frame = nullptr;
	Vector<SpriteFrame *> sprite_frames(20);
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

	button_start_event_listener->onTouchEnded = [](Touch *touch, Event *event)->void {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertTouchToNodeSpace(touch);
		Size size = target->getContentSize();
		Rect rect = Rect(0 + 40, 0 + 30, size.width - 80, size.height / 3 + 15);
		if (rect.containsPoint(locationInNode)) {
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0001.png"));
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(button_start_event_listener, button_start);
}

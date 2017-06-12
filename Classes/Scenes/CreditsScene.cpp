#include "CreditsScene.h"
#include "Common/CommonMacro.h"
#include "WelcomeScene.h"


CreditsScene::CreditsScene() {
}


CreditsScene::~CreditsScene() {
}

bool CreditsScene::init() {
	if (!Layer::init()) {
		return false;
	}
	auto tile_top = Sprite::createWithSpriteFrameName("credits_tileTop.png");
	float scale = winSize.width / tile_top->getContentSize().width;
	tile_top->setScale(scale);
	tile_top->setAnchorPoint(Vec2(0, 1));
	tile_top->setPosition(0, winSize.height);
	this->addChild(tile_top, -1);

	auto tile_down = Sprite::createWithSpriteFrameName("credits_tile.png");
	tile_down->setScale(scale);
	tile_down->setAnchorPoint(Vec2(0, 1));
	tile_down->setPosition(0, winSize.height - tile_top->getBoundingBox().size.height + 5);
	this->addChild(tile_down, -1);

	auto tile_down2 = Sprite::createWithSpriteFrameName("credits_tile.png");
	tile_down2->setScale(scale);
	tile_down2->setAnchorPoint(Vec2(0, 1));
	tile_down2->setPosition(0, winSize.height - tile_top->getBoundingBox().size.height + 5 - tile_down->getBoundingBox().size.height);
	this->addChild(tile_down2, -1);

	auto sword = Sprite::createWithSpriteFrameName("credits_sword.png");
	sword->setScale(scale * 0.5);
	sword->setPosition(winSize.width - sword->getBoundingBox().size.width, winSize.height - sword->getBoundingBox().size.height / 2);
	this->addChild(sword, 0);

	auto credits_statement = Label::createWithTTF("Resources are for learning reference only, \n"
												  "not for any commericial purposes. \n"
												  "All copyrights are reserved to the original author.\n"
												  "Please delete it after downloading it within 24 hours.",
												  "fonts/Comic_Book.ttf",
												  23, Size(winSize.width * 0.8, 0));
	credits_statement->setHorizontalAlignment(TextHAlignment::CENTER);
	credits_statement->setTextColor(Color4B::BLACK);
	credits_statement->setPosition(winSize.width / 2, winSize.height * 2 / 3);
	this->addChild(credits_statement, 1);

	auto cap = 50.0f;

	auto credits_info = Label::createWithTTF("Program by Ranjam\n"
											 "https://github.com/Ranjam", 
											 "fonts/Marker Felt.ttf",
											 27);
	credits_info->setHorizontalAlignment(TextHAlignment::CENTER);
	credits_info->setTextColor(Color4B::BLACK);
	credits_info->setPosition(winSize.width / 2, credits_statement->getPosition().y - credits_statement->getContentSize().height / 2 - cap);
	this->addChild(credits_info, 1);

	auto cocos_label = Label::createWithTTF("Powered by", "fonts/Comic_Book.ttf", 30);
	cocos_label->setPosition(winSize.width / 2, credits_info->getPosition().y - credits_info->getContentSize().height / 2 - cap);
	cocos_label->setTextColor(Color4B::BLACK);
	this->addChild(cocos_label, 0);

	auto cocos_flag = Sprite::createWithSpriteFrameName("credits_cocos2d.png");
	cocos_flag->setScale(scale);
	cocos_flag->setPosition(winSize.width / 2, cocos_label->getPosition().y - cocos_label->getContentSize().height / 2 - cap);
	this->addChild(cocos_flag, 0);

	auto back_button = Sprite::createWithSpriteFrameName("credits_back_0001.png");
	back_button->setAnchorPoint(Vec2(0, 0));
	back_button->setScale(scale * 0.8);
	back_button->setPosition(0, -10);
	this->addChild(back_button, 0);

	auto back_listener = EventListenerTouchOneByOne::create();
	back_listener->onTouchBegan = [=](Touch *touch, Event *event)->bool {
		if (back_button->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch))) {
			back_button->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("credits_back_0002.png"));
			return true;
		}
		return false;
	};

	back_listener->onTouchEnded = [=](Touch *touch, Event *event) {
		auto scene = WelcomeScene::createScene();
		Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5f, scene));
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(back_listener, back_button);

	return true;
}

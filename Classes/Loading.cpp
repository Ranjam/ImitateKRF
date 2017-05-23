#include "Loading.h"
#include "Resources.h"


Loading::Loading() {
}


Loading::~Loading() {
}

bool Loading::init() {
	// load file
	loadingAssets();

	// load animation
	loadingAnimations();

	return true;
}

void Loading::loadingAssets() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_in_game_gui_plist);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_common_sprite_sheet);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_mainmenu_spritesheet);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_mainmenu_spritesheet2);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_sprite_level_0);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_enemy_desert_0);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_tower);
}

void Loading::loadingAnimations() {
	Vector<SpriteFrame *> sprites;
	SpriteFrame *sprite_frame;

	// desert thug running
	for (int i = 0; i < 23; ++i) {
		sprite_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("desertThug_00%02d.png", i));
		if (sprite_frame != nullptr) {
			sprites.pushBack(sprite_frame);
		}
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(sprites, 0.05f), 
												"desert_thug_move_forward");
	sprites.clear();

	// desert thug up
	for (int i = 23; i < 45; ++i) {
		sprite_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("desertThug_00%02d.png", i));
		if (sprite_frame != nullptr) {
			sprites.pushBack(sprite_frame);
		}
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(sprites, 0.05f), 
												"desert_thug_move_up");
	sprites.clear();

	// desert thug down
	for (int i = 47; i < 67; ++i) {
		sprite_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("desertThug_00%02d.png", i));
		if (sprite_frame != nullptr) {
			sprites.pushBack(sprite_frame);
		}
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(sprites, 0.05f),
												"desert_thug_move_down");
	sprites.clear();

	// desert thug attack
	for (int i = 67; i < 101; ++i) {
		sprite_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("desertThug_0%03d.png", i));
		if (sprite_frame != nullptr) {
			sprites.pushBack(sprite_frame);
		}
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(sprites, 0.05f),
												"desert_thug_attack");
	sprites.clear();

	// desert thug died
	for (int i = 101; i <= 106; ++i) {
		sprite_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("desertThug_0%03d.png", i));
		if (sprite_frame != nullptr) {
			sprites.pushBack(sprite_frame);
		}
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(sprites, 0.1f),
												"desert_thug_died");
	sprites.clear();

	// desert thug stand
	sprite_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("desertThug_0067.png"));
	if (sprite_frame != nullptr) {
		sprites.pushBack(sprite_frame);
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(sprites, 0.1f),
												"desert_thug_stand");
	sprites.clear();
}

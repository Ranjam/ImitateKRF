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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_enemy_desert_3);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_tower);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_map_sprite);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_common_sprite_sheet2);
}

void Loading::loadingAnimations() {


	// desert thug running
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_00%02d.png", 0, 22, 0.05f),
												"desert_thug_move_forward");

	// desert thug up
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_00%02d.png", 23, 44, 0.05f), 
												"desert_thug_move_up");

	// desert thug down
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_00%02d.png", 47, 66, 0.05f),
												"desert_thug_move_down");

	// desert thug attack
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_0%03d.png", 67, 100, 0.05f),
												"desert_thug_attack");

	// desert thug died
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_0%03d.png", 101, 106, 0.05f),
												"desert_thug_dead");

	// desert thug stand
	AnimationCache::getInstance()->addAnimation(createAnimation("desertThug_0067.png", 67, 67, 0.05f),
												"desert_thug_stand");

	// building smoke effect
	AnimationCache::getInstance()->addAnimation(createAnimation("effect_buildSmoke_00%02d.png", 1, 10, 0.1f),
												"building_smoke_effect");

	// archers tower lvx atack down
	Animation *animation;
	// lv1
	animation = createAnimation("tower_archer_lvl1_shooter_00%02d.png", 3, 10, 0.04f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tower_archer_lvl1_shooter_0001.png"));
	AnimationCache::getInstance()->addAnimation(animation, "archer_lv1_shoot_down");
	// lv2
	animation = createAnimation("tower_archer_lvl2_shooter_00%02d.png", 3, 10, 0.04f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tower_archer_lvl2_shooter_0001.png"));
	AnimationCache::getInstance()->addAnimation(animation, "archer_lv2_shoot_down");
	// lv3
	animation = createAnimation("tower_archer_lvl3_shooter_00%02d.png", 3, 10, 0.04f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tower_archer_lvl3_shooter_0001.png"));
	AnimationCache::getInstance()->addAnimation(animation, "archer_lv3_shoot_down");

	// archers tower lvx attack up
	// lv1
	animation = createAnimation("tower_archer_lvl1_shooter_00%02d.png", 11, 18, 0.04f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tower_archer_lvl1_shooter_0002.png"));
	AnimationCache::getInstance()->addAnimation(animation, "archer_lv1_shoot_up");
	// lv2
	animation = createAnimation("tower_archer_lvl2_shooter_00%02d.png", 11, 18, 0.04f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tower_archer_lvl2_shooter_0002.png"));
	AnimationCache::getInstance()->addAnimation(animation, "archer_lv2_shoot_up");
	// lv3
	animation = createAnimation("tower_archer_lvl3_shooter_00%02d.png", 11, 18, 0.04f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tower_archer_lvl3_shooter_0002.png"));
	AnimationCache::getInstance()->addAnimation(animation, "archer_lv3_shoot_up");
}

Animation* Loading::createAnimation(std::string files_name, int start_index, int end_index, float delay) {
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(delay);
	SpriteFrame *sprite_frame;
	for (int i = start_index; i <= end_index; ++i) {
		sprite_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(files_name.c_str(), i));
		if (sprite_frame != nullptr) {
			animation->addSpriteFrame(sprite_frame);
		}
	}
	return animation;
}

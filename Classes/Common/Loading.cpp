#include "Loading.h"
#include "Resources.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_credits_sprite);
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

	// logo animation
	AnimationCache::getInstance()->addAnimation(createAnimation("logo_brillo_00%02d.png", 1, 26, 0.1f), 
												"logo_animation");

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

	// reinforce A0 move
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_A0_00%02d.png", 1, 6, 0.1f),
												"reinforce_A0_move");

	// reinforce A0 attack
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_A0_00%02d.png", 6, 7, 0.5f),
												"reinforce_A0_attack");

	// reinforce_A1 move
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_A1_00%02d.png", 1, 6, 0.1f),
												"reinforce_A1_move");

	// reinforce_A1 attack
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_A1_00%02d.png", 7, 11, 0.1f),
												"reinforce_A1_attack");

	// reinforce_A3_ move
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_A3_00%02d.png", 1, 6, 0.1f),
												"reinforce_A3_move");

	// reinforce_A3_ attack
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_A3_00%02d.png", 7, 24, 0.05f),
												"reinforce_A3_attack");

	// reinforce_A3_ arrow
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_A3_00%02d.png", 25, 36, 0.05f),
												"reinforce_A3_arrow");

	// reinforce_B3_ move
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_B3_00%02d.png", 1, 6, 0.1f),
												"reinforce_B3_move");

	// reinforce_B3_ attack
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_B3_00%02d.png", 7, 24, 0.05f),
												"reinforce_B3_attack");

	// reinforce_B3_ arrow
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_B3_00%02d.png", 25, 39, 0.05f),
												"reinforce_B3_arrow");

	// reinforce_C3_ move
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_C3_00%02d.png", 1, 6, 0.1f),
												"reinforce_C3_move");

	// reinforce_C3_ attack
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_C3_00%02d.png", 7, 27, 0.05f),
												"reinforce_C3_attack");

	// reinforce_C3_ arrow
	AnimationCache::getInstance()->addAnimation(createAnimation("reinforce_C3_00%02d.png", 28, 42, 0.05f),
												"reinforce_C3_arrow");

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

	// fireball explosion
	AnimationCache::getInstance()->addAnimation(createAnimation("fireball_explosion_00%02d.png", 1, 17, 0.05f), "fireball_explosion");

	// fireball particle
	AnimationCache::getInstance()->addAnimation(createAnimation("fireball_particle_00%02d.png", 1, 4, 0.05f), "fireball_particle");

	// fireball shadow
	AnimationCache::getInstance()->addAnimation(createAnimation("fireball_shadow_00%02d.png", 1, 20, 0.05f), "fireball_shadow");

	// fireball proyectile
	AnimationCache::getInstance()->addAnimation(createAnimation("fireball_proyectile_00%02d.png", 1, 5, 0.05f), "fireball_proyectile");
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

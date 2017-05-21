#include "Loading.h"
#include "Resources.h"


Loading::Loading() {
}


Loading::~Loading() {
}

bool Loading::init() {
	// load file
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_in_game_gui_plist);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_common_sprite_sheet);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_mainmenu_spritesheet);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_mainmenu_spritesheet2);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_sprite_level_0);

	return true;
}

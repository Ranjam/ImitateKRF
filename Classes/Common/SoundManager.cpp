#include "SoundManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

void SoundManager::playMusic(const char *file_name, bool loop) {
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(file_name, loop);
}

void SoundManager::playEffect(const char *file_name, bool loop, float pitch, float pan, float gain) {
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
	SimpleAudioEngine::getInstance()->playEffect(file_name, loop, pitch, pan, gain);
}

void SoundManager::stopMusic(bool release) {
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(release);
}

void SoundManager::stopAllEffect() {
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

SoundManager::SoundManager() {
}


SoundManager::~SoundManager() {
}

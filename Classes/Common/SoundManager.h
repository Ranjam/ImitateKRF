#ifndef __SOUND_MANAGER_H__
#define	__SOUND_MANAGER_H__

class SoundManager {
public:
	static SoundManager *getInstance() {
		static SoundManager instance;
		return &instance;
	}

	void playMusic(const char *file_name, bool loop = false);

	void playEffect(const char *file_name, bool loop = false, float pitch = 1, float pan = 0, float gain = 1);

	void stopMusic(bool release = true);

	void stopAllEffect();
private:
	SoundManager();
	~SoundManager();
	SoundManager(const SoundManager &) = delete; 
	SoundManager &operator =(const SoundManager &) = delete;
};

#endif

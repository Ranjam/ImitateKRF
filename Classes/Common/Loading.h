#ifndef __LOADING_H__
#define __LOADING_H__

#include "cocos2d.h"

USING_NS_CC;

class Loading {
public:
	Loading();
	~Loading();

	bool init();

	void loadingAssets();

	void loadingAnimations();

	Animation *createAnimation(std::string files_name, int start_index, int end_index, float delay);
};

#endif

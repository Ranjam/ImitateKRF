
#ifndef WARNING_FLAG_H
#define WARNING_FLAG_H

#include "cocos2d.h"

USING_NS_CC;

class WarningFlag: public Sprite {
public:
	WarningFlag();
	~WarningFlag();

	static WarningFlag* create() {
		WarningFlag *pRet = new(std::nothrow) WarningFlag(); 
		if (pRet && pRet->init()) {
			pRet->autorelease(); 
			return pRet;
		}
		delete pRet; 
		pRet = nullptr; 
		return nullptr;
	}

	bool init() override;

	/**
	 * \brief set the progress speed.
	 * \param speed How much increase per second, the total is 100
	 */
	void setSpeed(float speed);

	float getPercentage() const;

	void start();

	void stop();

	void updateProgress(float dt);

	void respiration();

	bool isOver() const {
		return is_over_;
	}

	int getPath() const {
		return path_;
	}

	void setPath(int path) {
		path_ = path;
	}

private:
	ProgressTimer *progressTimer_;
	Sprite *selected_;
	float speed_ = 10.0f;
	bool is_selected_ = false;
	bool is_over_ = false;
	int path_;
};

#endif

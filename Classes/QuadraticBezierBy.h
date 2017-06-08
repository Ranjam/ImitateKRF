#ifndef __ARROW_BEZIER_PATH_H__
#define __ARROW_BEZIER_PATH_H__

#include "cocos2d.h"

USING_NS_CC;

// Quadratic B¨¦zier Configuration
struct ccQuadraticBezierConfig {
	Point controlPoint;
	Point endPosition;
};

/**
 * \brief An action that moves the target with a quadratic Bezier curve by a certain distance.
 */
class QuadraticBezierBy: public ActionInterval {
public:
	QuadraticBezierBy();
	~QuadraticBezierBy();

	/**
	 * \brief Creates the action with a duration and a quadratic bezier configuration.
     * @param duration Duration time, in seconds.
     * @param config Bezier config.
     * @param with_rotate Whether to set the direction when moving, if it is true, this action will change the rotaion of that object to tangent direction
     * @return An autoreleased QuadraticBezierBy object. 
	 */
	static QuadraticBezierBy* create(float duration, const ccQuadraticBezierConfig &config, bool with_rotate = false) {
		auto pRet = new(std::nothrow) QuadraticBezierBy(); 
		if (pRet && pRet->initWithDuration(duration, config, with_rotate)) {
			pRet->autorelease(); 
			return pRet;
		}
		delete pRet; 
		pRet = nullptr; 
		return nullptr;
	};

	bool initWithDuration(float duration, const ccQuadraticBezierConfig& config, bool with_rotate);

	void update(float time) override;

	bool getWithRotate() const {
		return _with_rotate;
	}

	void setWithRotate(bool with_rotate) {
		this->_with_rotate = with_rotate;
	}

private:
	ccQuadraticBezierConfig _config;
	Vec2 _start_position;
	Vec2 _previous_position;

	// whether to set the direction when moving
	bool _with_rotate = false;

private:
	QuadraticBezierBy(const QuadraticBezierBy &) = delete; 
	QuadraticBezierBy &operator =(const QuadraticBezierBy &) = delete;;
};

#endif

#include "ArrowBullet.h"



ArrowBullet::ArrowBullet() {
}


ArrowBullet::~ArrowBullet() {
}

bool ArrowBullet::init() {
	if (!BaseBullet::init()) {
		return false;
	}

	this->power_ = 10.0f;

	this->initWithSpriteFrameName("arrow.png");
	this->setFlippedX(true);

	return true;
}

void ArrowBullet::attack() {
	//this->runAction(Sequence::create(bullet_animation_, 
									 //CallFunc::create(CC_CALLBACK_0(ArrowBullet::destroy, this)),
									 //NULL));
}

void ArrowBullet::destroy() {
	this->removeFromParentAndCleanup(true);
}

// todo: update more beautiful curve
void ArrowBullet::shootBy(Vec2 delta_vec, float height, float duration, CallFunc *call_func) {

	// set the control point
	Vec2 mid_point = Vec2(delta_vec.x / 2, delta_vec.y > 0 ? delta_vec.y + height : height);
	ccBezierConfig bezier_config;
	bezier_config.controlPoint_1 = bezier_config.controlPoint_2 = mid_point;
	bezier_config.endPosition = delta_vec;

	// set the start angle and end angle
	float start_angle;
	if (fabs(delta_vec.x - 0) > 0.000001) {
		start_angle = CC_RADIANS_TO_DEGREES(atan(height / (delta_vec.x / 2)));
	} else {
		start_angle = -90;
	}
	float end_angle;
	if (delta_vec.x >= 0) {
		start_angle = -start_angle;
		end_angle = 75.0f;
	} else {
		start_angle = 180.0f - start_angle;
		end_angle = -255.0f;
	}
	this->setRotation(start_angle);

	Spawn *spawn;
	if (start_angle < -75 || start_angle > 255) {
		// if start angle approach right angle, direct flip angle
		spawn = Spawn::create(BezierTo::create(duration, bezier_config),
		                            Sequence::create(DelayTime::create(duration * (delta_vec.y > 0 ? 0.6f : 0.4f)), 
		                                             CallFunc::create([=]() {
				                                             this->setRotation(90);
			                                             }), 
		                                             NULL),
		                            NULL);
	} else {
		spawn = Spawn::create(BezierTo::create(duration, bezier_config),
							  Sequence::create(DelayTime::create(duration * 0.1f), 
											   RotateTo::create(duration * 0.9f, end_angle), 
											   NULL),
		                      NULL);
	}
	this->runAction(Sequence::create(spawn, call_func, NULL));
}

#include "QuadraticBezierBy.h"

// quadratic bezier formula
static inline float bezierat(float p0, float p1, float p2, float t) {
	return powf(1 - t, 2) * p0 + 2.0f * t * (1 - t) * p1 + powf(t, 2) * p2;
}

QuadraticBezierBy::QuadraticBezierBy() {
}

QuadraticBezierBy::~QuadraticBezierBy() {
}

bool QuadraticBezierBy::initWithDuration(float duration, const ccQuadraticBezierConfig& config, bool with_rotate) {

	if (!ActionInterval::initWithDuration(duration)) {
		return false;
	}

	_config = config;
	_with_rotate = with_rotate;

	return true;
}

void QuadraticBezierBy::update(float time) {
	if (_target) {
		float x_p0 = 0;
		float x_p1 = _config.controlPoint.x;
		float x_p2 = _config.endPosition.x;

		float y_p0 = 0;
		float y_p1 = _config.controlPoint.y;
		float y_p2 = _config.endPosition.y;

		float x = bezierat(x_p0, x_p1, x_p2, time);
		float y = bezierat(y_p0, y_p1, y_p2, time);

#if CC_ENABLE_STACKABLE_ACTIONS
		Vec2 current_pos = _target->getPosition();
		_start_position = _start_position + (current_pos - _previous_position);

		Vec2 new_pos = _start_position + Vec2(x, y);
		_target->setPosition(new_pos);

		_previous_position = new_pos;

		// rotate to tangent direction
		if (time != 0 && _with_rotate) {
			Vec2 relative_vec = new_pos - current_pos;
			float degrees = CC_RADIANS_TO_DEGREES(relative_vec.getAngle());
			_target->setRotation(-degrees);
		}
#else
		_target->setPosition(_start_position + Vec2(x, y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS
	}
}

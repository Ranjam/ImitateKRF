#include "FireballBullet.h"



FireballBullet::FireballBullet() {
}


FireballBullet::~FireballBullet() {
}

bool FireballBullet::init() {
	if (!BaseBullet::init()) {
		return false;
	}

	this->power_ = 10;

	// fireball_proyectile_0001.png
	fire_ball_ = Sprite::createWithSpriteFrameName("fireball_proyectile_0001.png");
	this->addChild(fire_ball_, 0);
	fire_ball_->setPosition(0, 800.0f);
	fire_ball_->setRotation(90);
	auto fireball_animate = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("fireball_proyectile")));
	fire_ball_->runAction(fireball_animate);
	auto sequence = Sequence::create(MoveTo::create(0.6f, Vec2(0, 0)),
									 CallFunc::create(CC_CALLBACK_0(FireballBullet::explode, this)),
									 NULL);
	fire_ball_->runAction(sequence);

	// particle
	schedule(schedule_selector(FireballBullet::particleEffect), 0.01f);

	// fireball_shadow_00%02d.png
	auto shadow = Sprite::createWithSpriteFrameName("fireball_shadow_0001.png");
	this->addChild(shadow, 2);
	shadow->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("fireball_shadow")),
									   CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, shadow)),
									   NULL));

	return true;
}

void FireballBullet::attack() {
	
}

void FireballBullet::destroy() {
	
}

void FireballBullet::particleEffect(float dt) {
	// fireball particle
	auto particle = Sprite::createWithSpriteFrameName("fireball_particle_0001.png");
	this->addChild(particle, 0);
	Vec2 pos = fire_ball_->getPosition();
	particle->setPosition(pos.x + RandomHelper::random_real(-5.0f, 5.0f), pos.y);
	particle->setRotation(RandomHelper::random_real(0.0f, 360.0f));
	particle->setScale(RandomHelper::random_real(0.0f, 1.0f));
	particle->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("fireball_particle")),
										 CallFunc::create([=]() { particle->removeFromParent(); }),
										 NULL));
}

void FireballBullet::explode() {
	// fireball_explosion_00%02d.png
	auto explosion = Sprite::createWithSpriteFrameName("fireball_explosion_0001.png");
	this->addChild(explosion, 3);
	explosion->setPosition(fire_ball_->getPosition());
	unschedule(schedule_selector(FireballBullet::particleEffect));
	fire_ball_->removeFromParent();
	explosion->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("fireball_explosion")),
										  CallFunc::create(CC_CALLBACK_0(FireballBullet::removeFromParent, this)),
										  NULL));

}

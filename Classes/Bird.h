#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"
#include "Settings.h"

class Bird
{
public:

	Bird(cocos2d::Layer *layer);
	void Fall();
	void Fly() { isFalling = false; };
	void StopFlying() { isFalling = true; };
	void BirdAnimate();
	void BirdRotate();
	void checkPosition();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *happyBird;

	cocos2d::PhysicsBody *happyBody;

	bool isFalling;

	Settings settings;
};

#endif // __BIRD_H__

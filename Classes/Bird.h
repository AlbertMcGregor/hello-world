#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"
#include "Settings.h"

class Bird
{
public:

	Bird(cocos2d::Layer *layer);
	void fall();
	void fly() { IsFalling = false; };
	void stopFlying() { IsFalling = true; };
	void birdAnimate();
	void birdRotate();
	void checkPosition();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite* HappyBird;

	cocos2d::PhysicsBody* HappyBody;

	bool IsFalling;

	Settings settings;
};

#endif // __BIRD_H__

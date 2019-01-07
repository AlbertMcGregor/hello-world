#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class Bird
{
public:

	Bird(cocos2d::Layer *layer);
	void Fall();
	void Fly() { isFalling = false; };
	void StopFlying() { isFalling = true; };
	void BirdAnimate();
	void BirdRotate();
	void Pause();
	void checkPosition();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *happyBird;

	bool isFalling;

};

#endif // __BIRD_H__

#ifndef __BASE_H__
#define __BASE_H__

#include "cocos2d.h"

class Base 
{
public:
	Base();

	void SpawnBase(cocos2d::Layer *layer);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

};

#endif // __BASE_H__

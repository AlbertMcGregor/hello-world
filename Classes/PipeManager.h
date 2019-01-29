#ifndef __PIPE_MANAGER_H__
#define __PIPE_MANAGER_H__

#include "cocos2d.h"
#include "Settings.h"

class PipeManager 
{
public:
	PipeManager();

	void spawnPipe(cocos2d::Layer *layer);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite* TopPipe;
	cocos2d::Sprite* BottomPipe;

	Settings constants;

};

#endif // __PIPE_MANAGER_H__

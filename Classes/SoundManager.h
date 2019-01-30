#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

class SoundManager
{
	CocosDenshion::SimpleAudioEngine* beginEffect;
	CocosDenshion::SimpleAudioEngine* flapEffect;
	CocosDenshion::SimpleAudioEngine* pointEffect;
	CocosDenshion::SimpleAudioEngine* hitEffect;
public:
	void preloadAll();
	void playBeginEffect();
	void playFlapEffect();
	void playPointEffect();
	void playHitEffect();
};

#endif // __SOUND_MANAGER_H__

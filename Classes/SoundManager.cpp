#include "SoundManager.h"
#include "SimpleAudioEngine.h"

void SoundManager::preloadAll()
{
	beginEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	beginEffect->preloadEffect("audio/sfx_swooshing.wav");

	flapEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	flapEffect->preloadEffect("audio/sfx_wing.wav");

	pointEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	pointEffect->preloadEffect("audio/sfx_point.wav");

	hitEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	hitEffect->preloadEffect("audio/sfx_hit.wav");
};
void SoundManager::playBeginEffect()
{
	beginEffect->playEffect("audio/sfx_swooshing.wav");
};
void SoundManager::playFlapEffect()
{
	flapEffect->playEffect("audio/sfx_wing.wav");
};
void SoundManager::playPointEffect()
{
	pointEffect->playEffect("audio/sfx_point.wav");
};
void SoundManager::playHitEffect()
{
	hitEffect->playEffect("audio/sfx_hit.wav");
};

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "PipeManager.h"
#include "Bird.h"
#include "Settings.h"
#include "SoundManager.h"


class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	void PauseBirdG();

    bool init();

    CREATE_FUNC(GameScene);

private:

	unsigned int score;

	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void stopFlying(float dt);

	void update(float dt);

	void baseMovingController();
		
	void spawnPipe(float dt);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	
	bool onContactBegin(cocos2d::PhysicsContact &contact);

	PipeManager pipeManager;

	Bird *bird;

	Settings constants;

	SoundManager soundManager;
	
	cocos2d::PhysicsWorld *sceneWorld;

	cocos2d::Size visibleSize;

	cocos2d::Sprite *Base;
	cocos2d::Label *GetReady;

	cocos2d::Label *ScoreLabel;
	cocos2d::Label *InstructionLabel;

};

#endif // __GAME_SCENE_H__

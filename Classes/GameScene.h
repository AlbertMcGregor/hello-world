#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"
#include "Base.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    bool init();

    CREATE_FUNC(GameScene);

private:
	void setPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	bool onContactBegin(cocos2d::PhysicsContact &contact);

	void StopFlying(float dt);

	void update(float dt);

	cocos2d::PhysicsWorld *sceneWorld;

	void SpawnPipe(float dt);

	cocos2d::Size visibleSize;

	cocos2d::Sprite *Base;

	Pipe pipe;
	Bird *bird;

};

#endif // __GAME_SCENE_H__

#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__
#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    bool init();

    CREATE_FUNC(GameOverScene);


};

#endif // __GAME_OVER_SCENE_H__

#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

        
    CREATE_FUNC(MainMenuScene);

private:
	cocos2d::Sprite *base1;
	cocos2d::Sprite *bird;
	void GoToGameScene(Ref *sender);
	void BirdAnimate();
};

#endif // __MAIN_MENU_SCENE_H__

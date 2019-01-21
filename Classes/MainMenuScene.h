#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "Settings.h"
#include <string>

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

	void update(float) override;
		
    CREATE_FUNC(MainMenuScene);

private:
	cocos2d::Sprite *base;

	cocos2d::MoveBy *moveBy;

	cocos2d::Size visibleSize;

	cocos2d::Sprite *bird;

	void GoToGameScene(Ref *sender);

	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void BirdAnimate();

	float topPipeWidth;

	Settings settings;
};

#endif // __MAIN_MENU_SCENE_H__

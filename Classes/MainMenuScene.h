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

	Settings settings;
		
    CREATE_FUNC(MainMenuScene);

private:
	cocos2d::Sprite *Base;

	cocos2d::MoveBy *moveBy;

	cocos2d::Size visibleSize;

	cocos2d::Sprite *Bird;

	void goToGameScene();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void birdAnimate();

	float topPipeWidth;
};

#endif // __MAIN_MENU_SCENE_H__

#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Param.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }

	auto happySlash = Sprite::create("HelloWorld.png");
	
	happySlash->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));

	this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), TRANSITION_TIME);
	
	this->addChild(happySlash);
	
    return true;
}

void SplashScene::GoToMainMenuScene(float dt)
{
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(DISPLAY_TIME_SPLASH_SCENE, scene));
}




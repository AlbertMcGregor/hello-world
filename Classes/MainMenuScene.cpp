#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }

	auto background = Sprite::create("HappyBirdSlash.jpg");
	background->setScaleX(Director::getInstance()->getVisibleSize().width / background->getContentSize().width);
	background->setScaleY(Director::getInstance()->getVisibleSize().height / background->getContentSize().height);
	background->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));

	auto playItem = MenuItemImage::create("playButtonNormal.png", "playButtonNormal.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
	playItem->setScale(0.35);
	
	auto menu = Menu::createWithItem(playItem);
	menu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 4 * 3,
		                       Director::getInstance()->getVisibleSize().height / 4 * 1.2));


	this->addChild(background);
	this->addChild(menu);

    return true;
}

void MainMenuScene::GoToGameScene(Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}





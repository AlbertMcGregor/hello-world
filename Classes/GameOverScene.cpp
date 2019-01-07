#include "GameOverScene.h"
#include "GameScene.h"

USING_NS_CC;

unsigned int score;

Scene* GameOverScene::createScene(unsigned int tempScore)
{
	score = tempScore;

	auto scene = Scene::create();
	auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameOverScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto menuItem = MenuItemImage::create("start-button.png", "start-button.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
	auto menu = Menu::createWithItem(menuItem);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));

	__String *string = __String::createWithFormat("%i", score);
	auto scoreLabel = Label::createWithTTF(string->getCString(), "Marker Felt.ttf", visibleSize.height * 0.14);
	auto highScoreLabel = Label::createWithTTF("0", "Marker Felt.ttf", visibleSize.height * 0.14);
	auto scoreText = Label::createWithTTF("SCORE", "Marker Felt.ttf", visibleSize.height * 0.1);
	auto highScoreText = Label::createWithTTF(" HIGH SCORE", "Marker Felt.ttf", visibleSize.height * 0.1);

	scoreLabel->setPosition(Vec2(visibleSize.width / 3, visibleSize.height / 2));
	highScoreLabel->setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height / 2));
	scoreText->setPosition(Vec2(visibleSize.width / 3, visibleSize.height * 0.7));
	highScoreText->setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height * 0.7));

	this->addChild(menu);
	this->addChild(scoreLabel);
	this->addChild(highScoreLabel);
	this->addChild(scoreText);
	this->addChild(highScoreText);

	return true;
}

void GameOverScene::GoToGameScene(Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}










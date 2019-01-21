#include "GameOverScene.h"
#include "GameScene.h"
#include "Settings.h"

USING_NS_CC;

using namespace std;

int score;

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

	Settings settings;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	UserDefault *def = UserDefault::getInstance();
	auto highScore = def->getIntegerForKey("HIGHSCORE", 0);

	// Вариант с хранением highscore пока не работает корректно: не удалётся перезаписать "HIGHSCORE" в json файле
	//int highScore = settings.jsonsettings["HIGHSCORE"].GetInt();
	
	if (score > highScore)
	{
		def->setIntegerForKey("HIGHSCORE", score);
		//settings.jsonsettings["HIGHSCORE"].SetInt(score);
		highScore = def->getIntegerForKey("HIGHSCORE", 0);
		//highScore = settings.jsonsettings["HIGHSCORE"].GetInt();
		//settings.jsonsettings.SetInt(score);
	}

	def->flush();

	auto menuItem = MenuItemImage::create("start-button.png", "start-button.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
	auto menuRetry = Menu::createWithItem(menuItem);
	menuRetry->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));

	this->addChild(menuRetry);

	auto startButtonText = Label::createWithTTF("RETRY", "flappy-bird.ttf", visibleSize.height * 0.1);
	startButtonText->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.35));

	this->addChild(startButtonText);
	
	__String *tempScore = __String::createWithFormat("%i", score);
	auto scoreLabel = Label::createWithTTF(tempScore->getCString(), "flappy-bird.ttf", visibleSize.height * 0.15);
	scoreLabel->setPosition(Vec2(visibleSize.width / 3, visibleSize.height * 0.5));

	this->addChild(scoreLabel);

	__String *tempHighScore = __String::createWithFormat("%i", highScore);
	auto highScoreLabel = Label::createWithTTF(tempHighScore->getCString(), "flappy-bird.ttf", visibleSize.height * 0.15);
	highScoreLabel->setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height * 0.5));

	this->addChild(highScoreLabel);

	auto scoreText = Label::createWithTTF("\nSCORE", "flappy-bird.ttf", visibleSize.height * 0.12);
	scoreText->setPosition(Vec2(visibleSize.width / 3, visibleSize.height * 0.7));

	this->addChild(scoreText);

	auto highScoreText = Label::createWithTTF(" HIGH\nSCORE", "flappy-bird.ttf", visibleSize.height * 0.12);
	highScoreText->setPosition(Vec2(visibleSize.width / 3 * 2, visibleSize.height * 0.7));

	this->addChild(highScoreText);

	auto gameOverText = Label::createWithTTF("GAME OVER", "flappy-bird.ttf", visibleSize.height * 0.15);
	gameOverText->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.9));
	this->addChild(gameOverText);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameOverScene::OnKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	return true;
}

void GameOverScene::GoToGameScene(Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOverScene::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
		case EventKeyboard::KeyCode::KEY_ENTER:
	{
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
}








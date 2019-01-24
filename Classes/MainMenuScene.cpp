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

	visibleSize = Director::getInstance()->getVisibleSize();

	auto Background = Sprite::create("images/Background.png");
	Background->setAnchorPoint(Vec2(0, 1));
	Background->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));
	
	Base = Sprite::create("images/baseLong2.png");
	Base->setAnchorPoint(Vec2(0, 1));
	Base->setPosition(0, visibleSize.height - Background->getContentSize().height);

	this->addChild(Background, -1);
	this->addChild(Base, 1);

	moveBy = MoveBy::create(settings.jsonsettings["PIPE_MOVEMENT_SPEED"].GetFloat() * visibleSize.width, Vec2(-visibleSize.width -
		Sprite::create("images/TopPipe.png")->getContentSize().width * settings.jsonsettings["PIPE_SCALE"].GetFloat(), 0));

	Base->runAction(moveBy);


	auto playItem = MenuItemImage::create("images/start-button.png", "images/start-button.png", CC_CALLBACK_0(MainMenuScene::goToGameScene, this));
	playItem->setScale(1.5);
	auto menu = Menu::createWithItem(playItem);
	menu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		                       Director::getInstance()->getVisibleSize().height / 2.8));
	this->addChild(menu);
	
	auto menuLabel = Label::createWithTTF("HappyBird", "fonts/flappy-bird.ttf", 200);
	menuLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.85));
	menuLabel->setTextColor(cocos2d::Color4B::WHITE);
	menuLabel->enableOutline(cocos2d::Color4B(0, 0, 0, 200));
	menuLabel->enableShadow(cocos2d::Color4B(0, 0, 0, 200), Size(2, -8));
	this->addChild(menuLabel);

	auto autorLabel = Label::createWithTTF("Powered by Albert Protopopov", "fonts/flappy-bird.ttf", 50);
	autorLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.12));
	autorLabel->setTextColor(cocos2d::Color4B::WHITE);
	autorLabel->enableShadow(cocos2d::Color4B(0, 0, 0, 200), Size(2, -2));
	this->addChild(autorLabel, 5);

	Bird = Sprite::create("images/bluebird-midflap.png");
	Bird->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	birdAnimate();
	this->addChild(Bird);


	auto vector = cocos2d::Vector<FiniteTimeAction*>();
	vector.pushBack(cocos2d::MoveBy::create(0.5, Vec2(0, 10)));
	vector.pushBack(cocos2d::MoveBy::create(0.5, Vec2(0, -10)));

	auto sequence = cocos2d::Sequence::create(vector);

	Bird->runAction(RepeatForever::create(sequence));

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MainMenuScene::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->scheduleUpdate();

    return true;
}

void MainMenuScene::update(float dt)
{
	
	Vec2 position = Base->getPosition();
	if (position.x < (-(visibleSize.width) - Sprite::create("images/TopPipe.png")->getContentSize().width *
		settings.jsonsettings["PIPE_SCALE"].GetFloat() + 10))
	{
		position.x = 0;
		Base->setPosition(position);

		auto moveBy = MoveBy::create(settings.jsonsettings["PIPE_MOVEMENT_SPEED"].GetFloat() * (visibleSize.width), Vec2(-visibleSize.width -
			Sprite::create("images/TopPipe.png")->getContentSize().width * settings.jsonsettings["PIPE_SCALE"].GetFloat(), 0));

		Base->runAction(moveBy);
	}

}

void MainMenuScene::goToGameScene()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainMenuScene::birdAnimate()
{
	Vector <SpriteFrame *> frames;
	frames.reserve(3);
	frames.pushBack(SpriteFrame::create("images/bluebird-upflap.png", Rect(0, 0, 34, 24)));
	frames.pushBack(SpriteFrame::create("images/bluebird-downflap.png", Rect(0, 0, 34, 24)));
	frames.pushBack(SpriteFrame::create("images/bluebird-midflap.png", Rect(0, 0, 34, 24)));

	auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
	auto animate = Animate::create(animation);

	Bird->runAction(RepeatForever::create(animate));
}

void MainMenuScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
		case EventKeyboard::KeyCode::KEY_ENTER:
	{
		MainMenuScene::goToGameScene();
	}
}









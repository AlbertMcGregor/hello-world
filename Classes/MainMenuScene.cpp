#include "MainMenuScene.h"
#include "GameScene.h"
#include "Param.h"

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

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto Background = Sprite::create("Background.png");
	Background->setAnchorPoint(Vec2(0, 1));
	Background->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));

	auto Base = Sprite::create("baseLong2.png");
	Base->setAnchorPoint(Vec2(0, 1));
	Base->setPosition(0, visibleSize.height - Background->getContentSize().height);

	auto moveBy = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width -
		Sprite::create("TopPipe.png")->getContentSize().width * PIPE_SCALE, 0));

	auto repeatForever = RepeatForever::create(moveBy);

	Base->runAction(repeatForever);

	this->addChild(Background, -1);
	this->addChild(Base, 1);

	auto playItem = MenuItemImage::create("start-button.png", "start-button.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
	playItem->setScale(1.5);
	auto menu = Menu::createWithItem(playItem);
	menu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		                       Director::getInstance()->getVisibleSize().height / 2.8));

	this->addChild(menu);

	auto menuLabel = Label::createWithTTF("HappyBird", "flappy-bird.ttf", 200);
	menuLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.85));
	menuLabel->setTextColor(cocos2d::Color4B::WHITE);
	menuLabel->enableOutline(cocos2d::Color4B::BLACK, 4);
	this->addChild(menuLabel);

	bird = Sprite::create("yellowbird-midflap.png");
	bird->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	BirdAnimate();
	this->addChild(bird);


	auto vector = cocos2d::Vector<FiniteTimeAction*>();
	vector.pushBack(cocos2d::MoveBy::create(0.5, Vec2(0, 10)));
	vector.pushBack(cocos2d::MoveBy::create(0.5, Vec2(0, -10)));

	auto sequence = cocos2d::Sequence::create(vector);

	bird->runAction(RepeatForever::create(sequence));

    return true;
}

void MainMenuScene::GoToGameScene(Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MainMenuScene::BirdAnimate()
{
	Vector <SpriteFrame *> frames;
	frames.reserve(3);
	frames.pushBack(SpriteFrame::create("yellowbird-upflap.png", Rect(0, 0, 34, 24)));
	frames.pushBack(SpriteFrame::create("yellowbird-downflap.png", Rect(0, 0, 34, 24)));
	frames.pushBack(SpriteFrame::create("yellowbird-midflap.png", Rect(0, 0, 34, 24)));

	auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
	auto animate = Animate::create(animation);

	bird->runAction(RepeatForever::create(animate));
}






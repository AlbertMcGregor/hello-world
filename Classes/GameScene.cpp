#include "GameScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "Bird.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }

	Director::getInstance()->pause();


	///////////////////////////////////    AUDIO EFFECTS    //////////////////////////////////////////////////


	auto effect = CocosDenshion::SimpleAudioEngine::getInstance();
	effect->preloadEffect("audio/sfx_swooshing.wav");
	effect->playEffect("audio/sfx_swooshing.wav");


	//////////////////////////////////    BACKGROUND & BASE    /////////////////////////////////////////////


	visibleSize = Director::getInstance()->getVisibleSize();

	auto Background = Sprite::create("images/Background.png");
	Background->setAnchorPoint(Vec2(0, 1));
	Background->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));

	Base = Sprite::create("images/baseLong2.png");
	Base->setAnchorPoint(Vec2(0, 1));
	Base->setPosition(0, visibleSize.height - Background->getContentSize().height);

	auto moveBy = MoveBy::create(constants.PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width -
		Sprite::create("images/TopPipe.png")->getContentSize().width * constants.PIPE_SCALE, 0));

	Base->runAction(moveBy);

	this->addChild(Background, -1);
	this->addChild(Base, 1);


	//////////////////////////////////////    INSTRUCTIONS    ////////////////////////////////////////////////


	GetReady = Label::createWithTTF("Get Ready!", "fonts/flappy-bird.ttf", visibleSize.height * 0.1);
	GetReady->setTextColor(Color4B(50, 205, 20, 255));
	GetReady->enableShadow(cocos2d::Color4B(0, 0, 0, 200), Size(2, -4));
	GetReady->enableOutline(cocos2d::Color4B::WHITE, 2);
	GetReady->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.7));
	this->addChild(GetReady, 1);

	InstructionLabel = Label::createWithTTF("click the left mouse button,\nupper arrow, enter, or space\nto fly",
		"fonts/flappy-bird.ttf", 50);
	InstructionLabel->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.5));
	InstructionLabel->setTextColor(Color4B(50, 205, 20, 255));
	InstructionLabel->enableShadow(cocos2d::Color4B(0, 0, 0, 200), Size(2, -4));
	InstructionLabel->enableOutline(cocos2d::Color4B::WHITE, 2);
	this->addChild(InstructionLabel, 1);



	////////////////////////////////////////    PHYSICS    /////////////////////////////////////////////////


	Size size(visibleSize.width, Background->getContentSize().height);

	auto edgeBody = PhysicsBody::createEdgeBox(size);
	edgeBody->setDynamic(false);
	edgeBody->setContactTestBitmask(false);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2,
	                       visibleSize.height / 2  + (visibleSize.height - Background->getContentSize().height) / 2));
	edgeNode->setPhysicsBody(edgeBody);

	Size sizeBase(visibleSize.width, visibleSize.height - Background->getContentSize().height);

	auto edgeBodyBase = PhysicsBody::createEdgeBox(sizeBase);
	edgeBodyBase->setCollisionBitmask(constants.OBSTACLE_COLLISION_BITMASK);
	edgeBodyBase->setContactTestBitmask(true);

	auto edgeNodeBase = Node::create();
	edgeNodeBase->setPosition(Vec2(visibleSize.width / 2, 
		(visibleSize.height - Background->getContentSize().height)/ 2));
	edgeNodeBase->setPhysicsBody(edgeBodyBase);

	this->addChild(edgeNode);
	this->addChild(edgeNodeBase);

	this->schedule(schedule_selector(GameScene::spawnPipe), constants.PIPE_SPAWN_FREQUENCY * visibleSize.width);

	bird = new Bird(this);


	/////////////////////////////////////////    LISTENERS    ////////////////////////////////////////////////


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);



	///////////////////////////////////////    ADDING THE SCORE LABEL    //////////////////////////////////////////////


	score = 0;

	__String *tempScore = __String::createWithFormat("%i", score);
	ScoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/flappy-bird.ttf", visibleSize.height * 0.2);
	ScoreLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.8));
	ScoreLabel->setColor(Color3B::WHITE);

	this->addChild(ScoreLabel, 200);

	this->scheduleUpdate();

	return true;
}


///////////////////////////////////////////    METHODS IMPLEMENTATIONS    ////////////////////////////////////////////


void GameScene::spawnPipe(float dt)
{
	pipeManager.spawnPipe(this);
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	if (Director::getInstance()->isPaused())
	{
		Director::getInstance()->resume();
		GetReady->setVisible(false);
		InstructionLabel->setVisible(false);
	}

	bird->fly();

	flapEffect();

	this->scheduleOnce(schedule_selector(GameScene::stopFlying), constants.BIRD_FLY_DURATION);

	bird->birdAnimate();

	return true;
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,cocos2d::Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_ENTER:
	  {
		if (Director::getInstance()->isPaused())
		{
			Director::getInstance()->resume();
			GetReady->setVisible(false);
			InstructionLabel->setVisible(false);
		}

		bird->fly();

		flapEffect();

		this->scheduleOnce(schedule_selector(GameScene::stopFlying), constants.BIRD_FLY_DURATION);

		bird->birdAnimate();
	  }
	  break;
	}
}


bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if (constants.BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && 
		constants.OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() ||
		constants.BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && 
		constants.OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask())
	{

		hitEffect();
		
		auto scene = GameOverScene::createScene(score);

		Director::getInstance()->replaceScene(scene);
	}

	if (constants.BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && 
		constants.POINT_COLLISION_BITMASK == b->getCollisionBitmask() ||
		constants.BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && 
		constants.POINT_COLLISION_BITMASK == a->getCollisionBitmask())
	{
		
		pointEffect();
	    
		score++;

        
		__String *tempScore = __String::createWithFormat("%i", score);
		ScoreLabel->setString(tempScore->getCString());
	}

	return true;
}


void GameScene::stopFlying(float dt)
{
	bird->stopFlying();
}


void GameScene::update(float dt)
{
	bird->fall();
	bird->birdRotate();
	bird->checkPosition();
	baseMovingController();
}

void GameScene::flapEffect()
{
	auto effect = CocosDenshion::SimpleAudioEngine::getInstance();
	effect->preloadEffect("audio/sfx_wing.wav");
	effect->playEffect("audio/sfx_wing.wav");
}

void GameScene::pointEffect()
{
	auto effect = CocosDenshion::SimpleAudioEngine::getInstance();
	effect->preloadEffect("audio/sfx_point.wav");
	effect->playEffect("audio/sfx_point.wav");
}

void GameScene::hitEffect()
{
	auto effect = CocosDenshion::SimpleAudioEngine::getInstance();
	effect->preloadEffect("audio/sfx_hit.wav");
	effect->playEffect("audio/sfx_hit.wav");
}

void GameScene::baseMovingController()
{
	Vec2 position = Base->getPosition();
	if (position.x < (-(visibleSize.width) - Sprite::create("images/TopPipe.png")->getContentSize().width * 
		constants.PIPE_SCALE + 10))
	{
		position.x = 0;
		Base->setPosition(position);

		auto moveBy = MoveBy::create(constants.PIPE_MOVEMENT_SPEED * (visibleSize.width), Vec2(-visibleSize.width -
			Sprite::create("images/TopPipe.png")->getContentSize().width * constants.PIPE_SCALE, 0));

		Base->runAction(moveBy);
	}
}
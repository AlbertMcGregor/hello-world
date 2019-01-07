#include "GameScene.h"
#include "GameOverScene.h"
#include "Param.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
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

	auto effect = CocosDenshion::SimpleAudioEngine::getInstance();
	effect->preloadEffect("sfx_swooshing.wav");
	effect->playEffect("sfx_swooshing.wav");

	visibleSize = Director::getInstance()->getVisibleSize();

	auto Background = Sprite::create("Background.png");
	Background->setAnchorPoint(Vec2(0, 1));
	Background->setPosition(Vec2(0, Director::getInstance()->getVisibleSize().height));

	Base = Sprite::create("baseLong2.png");
	Base->setAnchorPoint(Vec2(0, 1));
	Base->setPosition(0, visibleSize.height - Background->getContentSize().height);

	auto moveBy = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width -
		Sprite::create("TopPipe.png")->getContentSize().width * PIPE_SCALE, 0));

	auto repeatForever = RepeatForever::create(moveBy);

	Base->runAction(repeatForever);
	
	this->addChild(Background, -1);
	this->addChild(Base, 1);

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
	edgeBodyBase->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBodyBase->setContactTestBitmask(true);

	auto edgeNodeBase = Node::create();
	edgeNodeBase->setPosition(Vec2(visibleSize.width / 2, 
		(visibleSize.height - Background->getContentSize().height)/ 2));
	edgeNodeBase->setPhysicsBody(edgeBodyBase);

	this->addChild(edgeNode);
	this->addChild(edgeNodeBase);

	this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);

	bird = new Bird(this);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	score = 0;

	__String *tempScore = __String::createWithFormat("%i", score);
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "Marker Felt.ttf", visibleSize.height * 0.1);
	scoreLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.8));
	scoreLabel->setColor(Color3B::WHITE);

	this->addChild(scoreLabel, 200);

	this->scheduleUpdate();

	return true;
}


void GameScene::SpawnPipe(float dt)
{
	pipe.SpawnPipe(this);
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	bird->Fly();

	flapEffect();

	this->scheduleOnce(schedule_selector(GameScene::StopFlying), BIRD_FLY_DURATION);

	bird->BirdAnimate();

	return true;
}


bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if (BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() ||
		BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask())
	{
		hitEffect();
		
		auto scene = GameOverScene::createScene(score);

	    Director::getInstance()->replaceScene(scene);

	}

	if (BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask() ||
		BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask())
	{
		
		pointEffect();
	    
		score++;

		__String *tempScore = __String::createWithFormat("%i", score);
		scoreLabel->setString(tempScore->getCString());
	}

	return true;
}


void GameScene::StopFlying(float dt)
{
	bird->StopFlying();
}


void GameScene::update(float dt)
{
	bird->Fall();
	bird->BirdRotate();
	baseMoving();
	bird->checkPosition();
}


void GameScene::baseMoving()
{
	auto position = Base->getPosition();

	if (position.x < (0 - (Base->getContentSize().width - visibleSize.width - 50)))
	{
		position.x = 0;
	}

	Base->setPosition(position);
}


void GameScene::flapEffect()
{
	auto effect = CocosDenshion::SimpleAudioEngine::getInstance();
	effect->preloadEffect("sfx_wing.wav");
	effect->playEffect("sfx_wing.wav");
}

void GameScene::pointEffect()
{
	auto effect = CocosDenshion::SimpleAudioEngine::getInstance();
	effect->preloadEffect("sfx_point.wav");
	effect->playEffect("sfx_point.wav");
}

void GameScene::hitEffect()
{
	auto effect = CocosDenshion::SimpleAudioEngine::getInstance();
	effect->preloadEffect("sfx_hit.wav");
	effect->playEffect("sfx_hit.wav");
}
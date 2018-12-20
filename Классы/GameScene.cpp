#include "GameScene.h"
#include "GameOverScene.h"
#include "Param.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto background1 = Sprite::create("background-day.png");
	background1->setAnchorPoint(Vec2(0, 1));
	background1->setPosition(Vec2(0, getContentSize().height));

	auto background2 = Sprite::create("background-day.png");
	background2->setAnchorPoint(Vec2(0, 1));
	background2->setPosition(Vec2(background1->getContentSize().width, getContentSize().height));

	auto background3 = Sprite::create("background-day.png");
	background3->setAnchorPoint(Vec2(0, 1));
	background3->setPosition(Vec2(background1->getContentSize().width * 2, getContentSize().height));

	auto background4 = Sprite::create("background-day.png");
	background4->setAnchorPoint(Vec2(0, 1));
	background4->setPosition(Vec2(background1->getContentSize().width * 3, getContentSize().height));

	auto base1 = Sprite::create("base.png");
	base1->setScaleY(1.3);
	base1->setAnchorPoint(Vec2(0, 1));
	base1->setPosition(Vec2(0, getContentSize().height - background1->getContentSize().height));

	auto base2 = Sprite::create("base.png");
	base2->setScaleY(1.3);
	base2->setAnchorPoint(Vec2(0, 1));
	base2->setPosition(Vec2(base1->getContentSize().width, getContentSize().height - background1->getContentSize().height));

	auto base3 = Sprite::create("base.png");
	base3->setScaleY(1.3);
	base3->setAnchorPoint(Vec2(0, 1));
	base3->setPosition(Vec2(base1->getContentSize().width * 2, getContentSize().height - background1->getContentSize().height));

	this->addChild(background1, -1);
	this->addChild(background2, -1);
	this->addChild(background3, -1);
	this->addChild(background4, -1);
	this->addChild(base1, 1);
	this->addChild(base2, 1);
	this->addChild(base3, 1);

	Size size(visibleSize.width, background1->getContentSize().height);

	auto edgeBody = PhysicsBody::createEdgeBox(size);
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();

	edgeNode->setPosition(Vec2(visibleSize.width / 2,
		                       visibleSize.height / 2  + (visibleSize.height - background1->getContentSize().height) / 2));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);

	bird = new Bird(this);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

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
	this->scheduleOnce(schedule_selector(GameScene::StopFlying), BIRD_FLY_DURATION);

	return true;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if (BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() ||
		BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask())
	{
		auto scene = GameOverScene::createScene();
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
}






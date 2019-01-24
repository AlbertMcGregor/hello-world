#include "PipeManager.h"

USING_NS_CC;

PipeManager::PipeManager()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void PipeManager::spawnPipe(cocos2d::Layer *layer)
{
	auto TopPipe = Sprite::create("images/TopPipe.png");
	auto BottomPipe = Sprite::create("images/BottomPipe.png");
	TopPipe->setScaleY(settings.jsonsettings["PIPE_SCALE"].GetFloat());
	BottomPipe->setScaleY(settings.jsonsettings["PIPE_SCALE"].GetFloat());

	auto TopPipeBody = PhysicsBody::createBox(TopPipe->getContentSize());
	auto BottomPipeBody = PhysicsBody::createBox(BottomPipe->getContentSize());

	TopPipeBody->setDynamic(false);
	BottomPipeBody->setDynamic(false);

	TopPipeBody->setCollisionBitmask(0x000002);
	BottomPipeBody->setCollisionBitmask(0x000002);
	TopPipeBody->setContactTestBitmask(true);
	BottomPipeBody->setContactTestBitmask(true);

	TopPipe->setPhysicsBody(TopPipeBody);
	BottomPipe->setPhysicsBody(BottomPipeBody);

	auto backSize = Sprite::create("images/Background.png")->getContentSize();

	auto random = CCRANDOM_0_1();

    if (random > settings.jsonsettings["UPPER_PIPE_SCREEN_THRESHOLD"].GetFloat())
	{
		random = settings.jsonsettings["UPPER_PIPE_SCREEN_THRESHOLD"].GetFloat();
	}
	if (random < settings.jsonsettings["LOWER_PIPE_SCREEN_THRESHOLD"].GetFloat())
	{
		random = settings.jsonsettings["LOWER_PIPE_SCREEN_THRESHOLD"].GetFloat();
	}

	auto topPipePosition = (random * backSize.height + (visibleSize.height - backSize.height) +
		                                                 TopPipe->getContentSize().height / 2 * 
														 settings.jsonsettings["PIPE_SCALE"].GetFloat() + 
														 settings.jsonsettings["PIPE_GAP"].GetFloat() / 2);

	TopPipe->setPosition(Point(visibleSize.width + TopPipe->getContentSize().width / 2 * settings.jsonsettings["PIPE_SCALE"].GetFloat(),
		topPipePosition));

	BottomPipe->setPosition(Point(TopPipe->getPositionX(), topPipePosition - settings.jsonsettings["PIPE_GAP"].GetFloat() / 2 - 
		BottomPipe->getContentSize().height * settings.jsonsettings["PIPE_SCALE"].GetFloat()));

	layer->addChild(TopPipe);

	layer->addChild(BottomPipe);

	auto topPipeAction = MoveBy::create(settings.jsonsettings["PIPE_MOVEMENT_SPEED"].GetFloat() * visibleSize.width, Point(-visibleSize.width -
		TopPipe->getContentSize().width * settings.jsonsettings["PIPE_SCALE"].GetFloat(), 0));
	

	TopPipe->runAction(topPipeAction);
	BottomPipe->runAction(topPipeAction->clone());

	auto PointNode = Node::create();

	auto PointBody = PhysicsBody::createBox(Size(1, settings.jsonsettings["PIPE_GAP"].GetFloat()));
	PointBody->setDynamic(false);
	PointBody->setCollisionBitmask(settings.jsonsettings["POINT_COLLISION_BITMASK"].GetFloat());
	PointBody->setContactTestBitmask(true);

	PointNode->setPhysicsBody(PointBody);
	PointNode->setPosition(Vec2(TopPipe->getPositionX(), TopPipe->getPositionY() - TopPipe->getContentSize().height / 2 -
		settings.jsonsettings["PIPE_GAP"].GetFloat() / 2));

	layer->addChild(PointNode);

	auto pointAction = MoveBy::create(settings.jsonsettings["PIPE_MOVEMENT_SPEED"].GetFloat() * visibleSize.width, Point(-visibleSize.width -
		TopPipe->getContentSize().width * settings.jsonsettings["PIPE_SCALE"].GetFloat(), 0));
	PointNode->runAction(pointAction);
}








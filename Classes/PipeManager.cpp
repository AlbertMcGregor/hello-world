#include "PipeManager.h"

USING_NS_CC;

PipeManager::PipeManager()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void PipeManager::SpawnPipe(cocos2d::Layer *layer)
{
	auto topPipe = Sprite::create("TopPipe.png");
	auto bottomPipe = Sprite::create("BottomPipe.png");
	topPipe->setScaleY(settings.jsonsettings["PIPE_SCALE"].GetFloat());
	bottomPipe->setScaleY(settings.jsonsettings["PIPE_SCALE"].GetFloat());

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

	topPipeBody->setDynamic(false);
	bottomPipeBody->setDynamic(false);

	topPipeBody->setCollisionBitmask(0x000002);
	bottomPipeBody->setCollisionBitmask(0x000002);
	topPipeBody->setContactTestBitmask(true);
	bottomPipeBody->setContactTestBitmask(true);

	topPipe->setPhysicsBody(topPipeBody);
	bottomPipe->setPhysicsBody(bottomPipeBody);

	auto backSize = Sprite::create("background-day.png")->getContentSize();

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
		                                                 topPipe->getContentSize().height / 2 * 
														 settings.jsonsettings["PIPE_SCALE"].GetFloat() + 
														 settings.jsonsettings["PIPE_GAP"].GetFloat() / 2);

	topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width / 2 * settings.jsonsettings["PIPE_SCALE"].GetFloat(),
		topPipePosition));

	bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - settings.jsonsettings["PIPE_GAP"].GetFloat() / 2 - 
		bottomPipe->getContentSize().height * settings.jsonsettings["PIPE_SCALE"].GetFloat()));

	layer->addChild(topPipe);

	layer->addChild(bottomPipe);

	auto topPipeAction = MoveBy::create(settings.jsonsettings["PIPE_MOVEMENT_SPEED"].GetFloat() * visibleSize.width, Point(-visibleSize.width -
		topPipe->getContentSize().width * settings.jsonsettings["PIPE_SCALE"].GetFloat(), 0));
	

	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(topPipeAction->clone());

	auto pointNode = Node::create();

	auto pointBody = PhysicsBody::createBox(Size(1, settings.jsonsettings["PIPE_GAP"].GetFloat()));
	pointBody->setDynamic(false);
	pointBody->setCollisionBitmask(settings.jsonsettings["POINT_COLLISION_BITMASK"].GetFloat());
	pointBody->setContactTestBitmask(true);

	pointNode->setPhysicsBody(pointBody);
	pointNode->setPosition(Vec2(topPipe->getPositionX(), topPipe->getPositionY() - topPipe->getContentSize().height / 2 -
		settings.jsonsettings["PIPE_GAP"].GetFloat() / 2));

	layer->addChild(pointNode);

	auto pointAction = MoveBy::create(settings.jsonsettings["PIPE_MOVEMENT_SPEED"].GetFloat() * visibleSize.width, Point(-visibleSize.width -
		topPipe->getContentSize().width * settings.jsonsettings["PIPE_SCALE"].GetFloat(), 0));
	pointNode->runAction(pointAction);
}








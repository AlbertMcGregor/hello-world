#include "Pipe.h"
#include "Param.h"

USING_NS_CC;

Pipe::Pipe()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::SpawnPipe(cocos2d::Layer *layer)
{
	auto topPipe = Sprite::create("TopPipe.png");
	auto bottomPipe = Sprite::create("BottomPipe.png");
	topPipe->setScaleY(PIPE_SCALE);
	bottomPipe->setScaleY(PIPE_SCALE);

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

    if (random > UPPER_PIPE_SCREEN_THRESHOLD)
	{
		random = UPPER_PIPE_SCREEN_THRESHOLD;
	}
	if (random < LOWER_PIPE_SCREEN_THRESHOLD)
	{
		random = LOWER_PIPE_SCREEN_THRESHOLD;
	}

	auto topPipePosition = (random * backSize.height + (visibleSize.height - backSize.height)
			                                             + topPipe->getContentSize().height / 2 * PIPE_SCALE + PIPE_GAP / 2);

	topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width / 2 * PIPE_SCALE, topPipePosition));

	bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - PIPE_GAP / 2 - bottomPipe->getContentSize().height * PIPE_SCALE));

	layer->addChild(topPipe);

	layer->addChild(bottomPipe);

	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width - 
		topPipe->getContentSize().width * PIPE_SCALE, 0));
	

	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(topPipeAction->clone());

	auto pointNode = Node::create();

	auto pointBody = PhysicsBody::createBox(Size(1, PIPE_GAP));
	pointBody->setDynamic(false);
	pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
	pointBody->setContactTestBitmask(true);

	pointNode->setPhysicsBody(pointBody);
	pointNode->setPosition(Vec2(topPipe->getPositionX(), topPipe->getPositionY() - topPipe->getContentSize().height / 2 - PIPE_GAP / 2));

	layer->addChild(pointNode);

	auto pointAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width -
		topPipe->getContentSize().width * PIPE_SCALE, 0));
	pointNode->runAction(pointAction);
}

void Pipe::PausePipes()
{
	topPipe->pauseSchedulerAndActions();
	bottomPipe->pauseSchedulerAndActions();
}








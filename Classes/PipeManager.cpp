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
	TopPipe->setScaleY(constants.PIPE_SCALE);
	BottomPipe->setScaleY(constants.PIPE_SCALE);

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

    if (random > constants.UPPER_PIPE_SCREEN_THRESHOLD)
	{
		random = constants.UPPER_PIPE_SCREEN_THRESHOLD;
	}
	if (random < constants.LOWER_PIPE_SCREEN_THRESHOLD)
	{
		random = constants.LOWER_PIPE_SCREEN_THRESHOLD;
	}

	auto topPipePosition = (random * backSize.height + (visibleSize.height - backSize.height) +
		                                                 TopPipe->getContentSize().height / 2 * 
														 constants.PIPE_SCALE + 
														 constants.PIPE_GAP / 2);

	TopPipe->setPosition(Point(visibleSize.width + TopPipe->getContentSize().width / 2 * constants.PIPE_SCALE,
		topPipePosition));

	BottomPipe->setPosition(Point(TopPipe->getPositionX(), topPipePosition - constants.PIPE_GAP / 2 - 
		BottomPipe->getContentSize().height * constants.PIPE_SCALE));

	layer->addChild(TopPipe);

	layer->addChild(BottomPipe);

	auto topPipeAction = MoveBy::create(constants.PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width -
		TopPipe->getContentSize().width * constants.PIPE_SCALE, 0));
	

	TopPipe->runAction(topPipeAction);
	BottomPipe->runAction(topPipeAction->clone());

	auto PointNode = Node::create();

	auto PointBody = PhysicsBody::createBox(Size(1, constants.PIPE_GAP));
	PointBody->setDynamic(false);
	PointBody->setCollisionBitmask(constants.POINT_COLLISION_BITMASK);
	PointBody->setContactTestBitmask(true);

	PointNode->setPhysicsBody(PointBody);
	PointNode->setPosition(Vec2(TopPipe->getPositionX(), TopPipe->getPositionY() - TopPipe->getContentSize().height / 2 -
		constants.PIPE_GAP / 2));

	layer->addChild(PointNode);

	auto pointAction = MoveBy::create(constants.PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width -
		TopPipe->getContentSize().width * constants.PIPE_SCALE, 0));
	PointNode->runAction(pointAction);
}








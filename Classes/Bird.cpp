#include "Bird.h"
#include "Param.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	happyBird = Sprite::create("bluebird-midflap.png");
	happyBird->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto happyBody = PhysicsBody::createBox(happyBird->getContentSize());
	happyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	happyBody->setContactTestBitmask(true);

	happyBird->setPhysicsBody(happyBody);

	layer->addChild(happyBird, 100);

	isFalling = true;
}

void Bird::Fall()
{
	if (true == isFalling)
	{
		happyBird->setPositionX(visibleSize.width / 2 + origin.x);
		happyBird->setPositionY(happyBird->getPositionY() - (BIRD_FALLING_SPEED * visibleSize.height));
	}
	else
	{
		happyBird->setPositionX(visibleSize.width / 2 + origin.x);
		happyBird->setPositionY(happyBird->getPositionY() + (BIRD_FLYING_SPEED * visibleSize.height));
	}
}








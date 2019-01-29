#include "Bird.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	HappyBird = Sprite::create("images/bluebird-midflap.png");
	HappyBird->setPosition(Point(visibleSize.width / 3 , visibleSize.height / 2 + origin.y));

	HappyBody = PhysicsBody::createCircle(HappyBird->getContentSize().height / 2);
	HappyBody->setCollisionBitmask(constants.BIRD_COLLISION_BITMASK);
	HappyBody->setContactTestBitmask(true);

	HappyBird->setPhysicsBody(HappyBody);

	layer->addChild(HappyBird, 100);

	IsFalling = true;

}

void Bird::fall()
{

	if (true == IsFalling)
	{
		HappyBird->setPositionX(visibleSize.width / 3 + origin.x);
		HappyBird->setPositionY(HappyBird->getPositionY() - (constants.BIRD_FALLING_SPEED * visibleSize.height));
	}
	else
	{
		HappyBird->setPositionX(visibleSize.width / 3 + origin.x);
		HappyBird->setPositionY(HappyBird->getPositionY() + (constants.BIRD_FLYING_SPEED * visibleSize.height));
	}
}

	void Bird::birdAnimate()
	{
		Vector <SpriteFrame *> frames;
		frames.reserve(3);
		frames.pushBack(SpriteFrame::create("images/bluebird-upflap.png", Rect(0, 0, 34, 24)));
		frames.pushBack(SpriteFrame::create("images/bluebird-downflap.png", Rect(0, 0, 34, 24)));
		frames.pushBack(SpriteFrame::create("images/bluebird-midflap.png", Rect(0, 0, 34, 24)));

		auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
		auto animate = Animate::create(animation);

		HappyBird->runAction(Repeat::create(animate, 2));
	}

void Bird::birdRotate() {

	if ((HappyBird->getRotation()) < (-45))
	{
		HappyBird->setRotation(-45);
	}
	if ((HappyBird->getRotation()) > (90))
	{
		HappyBird->setRotation(90);
	}

	if (true == IsFalling)
	{

		HappyBird->setRotation(HappyBird->getRotation() + 4);

	}
	else

	{
		HappyBird->setRotation(HappyBird->getRotation() - 8);
	}
}

void Bird::checkPosition()
{
	auto y = HappyBird->getPositionY();
	if (y > visibleSize.height)
		HappyBird->setPositionY(visibleSize.height - 10);
}
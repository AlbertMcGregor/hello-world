#include "Bird.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	happyBird = Sprite::create("bluebird-midflap.png");
	happyBird->setPosition(Point(visibleSize.width / 3 , visibleSize.height / 2 + origin.y));

	happyBody = PhysicsBody::createCircle(happyBird->getContentSize().height / 2);
	happyBody->setCollisionBitmask(settings.jsonsettings["BIRD_COLLISION_BITMASK"].GetFloat());
	happyBody->setContactTestBitmask(true);

	happyBird->setPhysicsBody(happyBody);

	layer->addChild(happyBird, 100);

	isFalling = true;

}

void Bird::Fall()
{

	if (true == isFalling)
	{
		happyBird->setPositionX(visibleSize.width / 3 + origin.x);
		happyBird->setPositionY(happyBird->getPositionY() - (settings.jsonsettings["BIRD_FALLING_SPEED"].GetFloat() * visibleSize.height));
	}
	else
	{
		happyBird->setPositionX(visibleSize.width / 3 + origin.x);
		happyBird->setPositionY(happyBird->getPositionY() + (settings.jsonsettings["BIRD_FLYING_SPEED"].GetFloat() * visibleSize.height));
	}
}

	void Bird::BirdAnimate()
	{
		Vector <SpriteFrame *> frames;
		frames.reserve(3);
		frames.pushBack(SpriteFrame::create("bluebird-upflap.png", Rect(0, 0, 34, 24)));
		frames.pushBack(SpriteFrame::create("bluebird-downflap.png", Rect(0, 0, 34, 24)));
		frames.pushBack(SpriteFrame::create("bluebird-midflap.png", Rect(0, 0, 34, 24)));

		auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
		auto animate = Animate::create(animation);

		happyBird->runAction(Repeat::create(animate, 2));
	}

void Bird::BirdRotate() {

	if ((happyBird->getRotation()) < (-45))
	{
		happyBird->setRotation(-45);
	}
	if ((happyBird->getRotation()) > (90))
	{
		happyBird->setRotation(90);
	}

	if (true == isFalling)
	{

		happyBird->setRotation(happyBird->getRotation() + 4);

	}
	else

	{
		happyBird->setRotation(happyBird->getRotation() - 8);
	}
}

void Bird::checkPosition()
{
	auto y = happyBird->getPositionY();
	if (y > visibleSize.height)
		happyBird->setPositionY(visibleSize.height - 10);
}
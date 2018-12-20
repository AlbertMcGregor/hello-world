#include "Base.h"
#include "Param.h"

USING_NS_CC;

Base::Base()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Base::SpawnBase(cocos2d::Layer *layer)
{
	auto Base = Sprite::create("baseLong.png");
	Base->setAnchorPoint(Vec2(0, 1));

	auto backSize = Sprite::create("background-day.png")->getContentSize();

	Base->setPosition(Vec2(0, visibleSize.height - Sprite::create("Background.png")->getContentSize().height));

    layer->addChild(Base);

	auto baseAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width - 
		Base->getContentSize().width, 0));
	
	Base->runAction(baseAction);

}








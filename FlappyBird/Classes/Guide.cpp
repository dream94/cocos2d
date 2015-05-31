#include "Guide.h"

USING_NS_CC;

Guide::Guide(void)
{
}

Guide::~Guide(void)
{
}

bool Guide::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto origin=Director::getInstance()->getVisibleOrigin();
	auto visibleSize=Director::getInstance()->getVisibleSize();

	//Ready±êÌâ
	title = Sprite::createWithSpriteFrameName("text_ready.png");
	title->setPosition(Point(origin.x+visibleSize.width*0.5,origin.y+visibleSize.height*0.8));
	this->addChild(title);

	//Íæ·¨ÌáÊ¾
	guide = Sprite::createWithSpriteFrameName("tutorial.png");
	guide->setPosition(Point(origin.x+visibleSize.width*0.5,origin.y+visibleSize.height*0.4));
	this->addChild(guide);

	listener=EventListenerTouchOneByOne::create();

	listener->onTouchBegan=[=](Touch * t,Event * e)
	{
		return true;
	};

	listener->onTouchEnded=[=](Touch *t,Event * e)
	{
		_eventDispatcher->removeEventListener(listener);
		
		auto fade = FadeOut::create(0.5f);
		auto fade_2 = FadeOut::create(0.5f);
		//µ­³öÖ®ºó£¬»Øµ÷É¾³ýº¯Êý£¬´Ó³¡¾°ÒÆ³ýÕâ2¸ö¶ÔÏó
		auto callback = CallFuncN::create(CC_CALLBACK_0(Guide::rmGuide,this));
		auto sequence = Sequence::create(fade,callback,NULL);
		guide->runAction(sequence);
		title->runAction(fade_2);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}
//ÒÆ³ýÕâ2¸öÔªËØ
void Guide::rmGuide()
{
	this->removeChild(title);
	this->removeChild(guide);
}
